#include <stdio.h>
#include <stdlib.h>
#include <includes.h>
#include <sys/alt_cache.h>

#include "queue.h"
#include "breakout.h"

void breakout_create_textures(display_info * display)
{
	int i,j;

	for(i=0; i<480; i++)
			for(j=0; j<800; j++)
				display->frame_buffer[0][i][j] = 0xff0000 + ((i*255/480) << 8);

	for(i=0; i<480; i++)
			for(j=0; j<800; j++)
				display->frame_buffer[3][i][j] = 0x0;

	for(i=-10; i<10; i++)
		for(j=-10; j<10;j++)
			IOWR(TEXTURES_BASE+IMG_BALL, (i+10)*20+(j+10), ((i*i+j*j) <= 90) ? 0x0 : 0x2a2a2a);

	for(i=0; i<100; i++)
		IOWR(TEXTURES_BASE, TEXTURE_PADDLE+i, (i*i/10)%2==0 ? 0x505050 : 0x000000);

	for(i=0; i<50; i++)
		IOWR(TEXTURES_BASE, TEXTURE_BRICK0+i, i%2==0 ? 0x005000 : 0x009000);

	for(i=0; i<50; i++)
		IOWR(TEXTURES_BASE, TEXTURE_BRICK1+i, i%2==0 ? 0x000050 : 0x000090);

	for(i=0; i<50; i++)
		IOWR(TEXTURES_BASE, TEXTURE_BRICK2+i, i%2==0 ? 0x500000 : 0x900000);

	for(i=0; i<50; i++)
		IOWR(TEXTURES_BASE, TEXTURE_BRICK3+i, i%2==0 ? 0x005050 : 0x009090);

	for(i=0; i<50; i++)
		IOWR(TEXTURES_BASE, TEXTURE_WALL+i, 0x4a4a4a);

	alt_dcache_flush_all();
}

void breakout_uninit(game_struct * g)
{
	g->state = NOGAME;
	queue_delete(g->events_queue);
	free(g->paddle);

	int i;
	for(i=0;i<3;i++)
		free(g->walls[i]);
}

void breakout_clear_screen(display_info *display)
{
	// Display background
	sprite * s = sprite_init(0,0, 800, 480, (alt_u32*) display->frame_buffer[3], 0, 0);
	display_add_sprite(display, s, 1);
	free(s);
}

void breakout_init(game_struct * g, char * level)
{
	display_info * display = g->periph.display_handle;

	// Stop the game
	if(g->state != NOGAME)
		breakout_uninit(g);

	breakout_clear_screen(display);

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
				g->bricks[i*14+j].s = sprite_init(45+j*50+j, 45+i*20+i, 50, 20, (alt_u32*) TEXTURES_BASE+TEXTURE_BRICK0+(g->bricks[i*14+j].value-1)*TEXTURE_BRICK_SIZE, 50, 0);
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
	g->paddle = sprite_init(300,440, 200, 20, (alt_u32*) TEXTURES_BASE+TEXTURE_PADDLE, 100, 0);

	// Initialize ball
	g->ball.s = sprite_init(g->paddle->x+100,g->paddle->y-20, 20,20, (alt_u32*) TEXTURES_BASE+IMG_BALL, 0, 0x2a2a2a);
	g->ball.v.x = 1;
	g->ball.v.y = -1;

	// Initialize walls
	g->walls[0] = sprite_init(0,0, 10, 440, (alt_u32*) TEXTURES_BASE+TEXTURE_WALL, 50, 0);
	g->walls[1] = sprite_init(0,0, 800, 10, (alt_u32*) TEXTURES_BASE+TEXTURE_WALL, 50, 0);
	g->walls[2] = sprite_init(790,0, 10, 440, (alt_u32*) TEXTURES_BASE+TEXTURE_WALL, 50, 0);

	// Initialize speed
	g->speed = 5;

	// Initialize lives
	g->lives = 3;

	// Initialize score
	g->score = 0;

	// Initialize events queue
	g->events_queue = queue_new(EVENT_QUEUE_SIZE);

	// Display background
	sprite * s = sprite_init(0,0, 800, 480, (alt_u32*) display->frame_buffer[0], 0, 0);
	display_add_sprite(display, s, 0);
	free(s);

	// Display walls
	for(i=0; i<3; i++)
		display_add_sprite(display, g->walls[i], 0);

	// Display bricks
	for(i=0; i< NBR_BRICKS; i++)
			if(g->bricks[i].enabled) display_add_sprite(display, g->bricks[i].s, 0);

	// Display ball
	display_add_sprite(display, g->ball.s, 0);

	// Display paddle
	display_add_sprite(display, g->paddle, 1);

	g->state = NOT_MOVING;
}
