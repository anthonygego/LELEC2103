#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <includes.h>
#include <sys/alt_cache.h>

#include "queue.h"
#include "breakout.h"
#include "simpletext.h"

void breakout_create_textures(game_struct * game)
{
	display_info * display = game->periph.display_handle;

	int i,j;

	for(i=0; i<480; i++)
		for(j=0; j<800; j++)
			display->frame_buffer[3][i][j] = 0x0;

	display_clear_screen(display);
	display_add_text(display, 175, 210, 0xffffff, tahomabold_32, 0, "Loading textures...");
	display_end_frame(display);

	for(i=0; i<480; i++)
			for(j=0; j<800; j++)
				display->frame_buffer[0][i][j] = 0xff0000 + ((i*255/480) << 8);

	// Loading textures from SD card

	alt_u32 * textures;
	size_t len;

	alt_u8 err;
	OSSemPend(game->periph.pic32_handle->sem, 0, &err);
	pic32_sendrpc(game->periph.pic32_handle, "textures.bin", 13, CYCLONE_RPC_FILE);
	while(!pic32_receive(game->periph.pic32_handle, (char **) &textures, &len, 0));
	OSSemPost(game->periph.pic32_handle->sem);

	for(i=0; i<8000; i++)
		IOWR(TEXTURES_BASE, i, textures[i]);

	for(i=0; i<4000; i++)
		IOWR(display->bricks_img[0], i, textures[8000+i]);

	free(textures);

	// Creating rest of textures

	for(i=0; i<4400; i++)
		display->wall_vert_img[i] =  i%3==0 ? 0x2a2a2a : 0x4a4a4a;

	for(i=0; i<8000; i++)
		display->wall_horiz_img[i] = i%3==0 ? 0x2a2a2a : 0x4a4a4a;

	// Flush the cache
	alt_dcache_flush_all();

	display_add_text(display, 500, 210, 0xffffff, tahomabold_32, 0, "OK");
	display_end_frame(display);
}

void breakout_uninit(game_struct * g)
{
	g->state = NOGAME;

	display_remove_sprite(g->periph.display_handle, g->ball.s);
	display_remove_sprite(g->periph.display_handle, g->paddle);

	// Free allocated resources
	queue_delete(g->events_queue);
	free(g->ball.s);
	free(g->paddle);

	int i;
	for(i=0;i<3;i++)
		free(g->walls[i]);
}

void breakout_init(game_struct * g, char * level)
{
	display_info * display = g->periph.display_handle;

	// Stop the game
	if(g->state != NOGAME)
		breakout_uninit(g);

	display_clear_screen(display);
	display_add_text(display, 250, 210, 0xffffff, tahomabold_32, 0, "Loading game...");
	display_end_frame(display);

	// Initialize bricks
	g->rbricks = 0;

	int i, j;
	for(i=0; i< 12; i++)
	{
		for(j=0; j < 14; level++)
		{
			g->bricks[i*14+j].enabled = 1;
			g->bricks[i*14+j].value = *level-'0';

			if(g->bricks[i*14+j].value > 0 && g->bricks[i*14+j].value < 5)
			{
				g->bricks[i*14+j].s = display_sprite_init(display, 45+j*50+j, 45+i*20+i, 50, 20, display->bricks_img[g->bricks[i*14+j].value-1], 0, 0);
				g->rbricks++;
				j++;
			}
			else if(*level == '*')
			{
				g->bricks[i*14+j].enabled = 0;
				j++;
			}
		}
	}

	// Initialize paddle
	g->paddle = display_sprite_init(display, 300,440, 200, 20, (alt_u32*) TEXTURES_BASE + IMG_PADDLE200, (alt_u8*) TEXTURES_BASE + ALPHA_PADDLE200*4, 1);

	// Initialize ball
	g->ball.s = display_sprite_init(display, g->paddle->x+100,g->paddle->y-20, 20,20, (alt_u32*) TEXTURES_BASE + IMG_BALL, (alt_u8*) TEXTURES_BASE + ALPHA_BALL*4, 2);
	g->ball.v.x = 1;
	g->ball.v.y = -1;

	// Initialize walls
	g->walls[0] = display_sprite_init(display, 0,0, 10, 440, display->wall_vert_img, 0, 0);
	g->walls[1] = display_sprite_init(display, 0,0, 800, 10, display->wall_horiz_img, 0, 0);
	g->walls[2] = display_sprite_init(display, 790,0, 10, 440, display->wall_vert_img, 0, 0);

	// Initialize speed
	g->speed = 5;

	// Initialize lives
	g->lives = 3;

	// Initialize score
	g->score = 0;

	// Initialize events queue
	g->events_queue = queue_new(EVENT_QUEUE_SIZE);

	// Display background
	sprite * s = display_sprite_init(display, 0,0, 800, 480, (alt_u32*) display->frame_buffer[0], 0, 0);
	display_add_sprite(display, s);
	free(s);

	// Display walls
	for(i=0; i<3; i++)
		display_add_sprite(display, g->walls[i]);

	// Display bricks
	for(i=0; i< NBR_BRICKS; i++)
			if(g->bricks[i].enabled) display_add_sprite(display, g->bricks[i].s);

	// Display on screen
	display_end_frame(display);

	// Display ball
	display_add_sprite(display, g->ball.s);

	// Display paddle
	display_add_sprite(display, g->paddle);

	g->state = NOT_MOVING;
}

alt_u8 breakout_collision(sprite *s1, sprite *s2)
{
	alt_u16 x1 = s1->x;
	alt_u16 y1 = s1->y;
	alt_u16 w1 = s1->width;
	alt_u16 h1 = s1->height;
	alt_u16 x2 = s2->x;
	alt_u16 y2 = s2->y;
	alt_u16 w2 = s2->width;
	alt_u16 h2 = s2->height;

	alt_u8 result = 0;
	if(!((x1 + w1 < x2) || (x2 + w2 < x1) || (y1 + h1 < y2) || (y2 + h2 < y1)))
	{
		if((x1 < x2 && x2 < x1 + w1) || (x1 < x2+w2 && x2+w2 < x1+w1))
			result = 1;
		else if((y1 < y2 && y2 < y1 + h1) || (y1 < y2+h2 && y2+h2 < y1+h1))
			result = 2;
	}

	return result;
}
