#include <stdio.h>
#include <stdlib.h>
#include <includes.h>
#include <sys/alt_cache.h>

#include "breakout.h"

void breakout_create_textures()
{
	int i,j;

	for(i=-10; i<10; i++)
		for(j=-10; j<10;j++)
			IOWR(TEXTURES_BASE+IMG_BALL, (i+10)*20+(j+10), ((i*i+j*j) <= 80) ? 0x0 : 0x2a2a2a);

	for(i=0; i<100; i=i+4) {
		IOWR(TEXTURES_BASE, TEXTURE_PADDLE+i, 0x0);
		IOWR(TEXTURES_BASE, TEXTURE_PADDLE+i+1, 0x0);
		IOWR(TEXTURES_BASE, TEXTURE_PADDLE+i+2, 0x0);
		IOWR(TEXTURES_BASE, TEXTURE_PADDLE+i+3, 0xa0a0a0);
	}

	for(i=0; i<50; i=i+3) {
		IOWR(TEXTURES_BASE, TEXTURE_BRICK0+i, 0x009000);
		IOWR(TEXTURES_BASE, TEXTURE_BRICK0+i+1, 0x009000);
		IOWR(TEXTURES_BASE, TEXTURE_BRICK0+i+2, 0x005000);
	}

	for(i=0; i<50; i=i+3) {
		IOWR(TEXTURES_BASE, TEXTURE_BRICK1+i, 0x000090);
		IOWR(TEXTURES_BASE, TEXTURE_BRICK1+i+1, 0x000090);
		IOWR(TEXTURES_BASE, TEXTURE_BRICK1+i+2, 0x000050);
	}

	for(i=0; i<50; i=i+3) {
		IOWR(TEXTURES_BASE, TEXTURE_BRICK2+i, 0x900000);
		IOWR(TEXTURES_BASE, TEXTURE_BRICK2+i+1, 0x900000);
		IOWR(TEXTURES_BASE, TEXTURE_BRICK2+i+2, 0x500000);
	}

	for(i=0; i<50; i=i+3) {
		IOWR(TEXTURES_BASE, TEXTURE_BRICK3+i, 0x009090);
		IOWR(TEXTURES_BASE, TEXTURE_BRICK3+i+1, 0x009090);
		IOWR(TEXTURES_BASE, TEXTURE_BRICK3+i+2, 0x005050);
	}

	for(i=0; i<50; i++)
		IOWR(TEXTURES_BASE, TEXTURE_WALL+i, 0x4a4a4a);
}

void breakout_clear_screen(display_info * display)
{
	int i,j;

	for(i=0; i<480; i++)
		for(j=0; j<800; j++)
			display->frame_buffer[0][i][j] = 0xff0000 + ((i*255/480) << 8);

	for(i=0; i<480; i++)
		for(j=0; j<800; j++)
			display->frame_buffer[1][i][j] = 0;

	for(i=0; i<480; i++)
		for(j=0; j<800; j++)
			display->frame_buffer[2][i][j] = 0;

}

void breakout_init(game_struct * g, char * level)
{
	display_info * display = g->periph.display_handle;

	// Stop the game
	g->state = NOGAME;

	// Clear screen and create textures
	breakout_clear_screen(display);
	breakout_create_textures();

	// Initialize bricks
	int i,j;
	char * buffer = level;
	for(i=0; i< 12; i++)
	{
		for(j=0; j< 14; j++)
		{
			char c;
			int read = sscanf(buffer, "%*[ \n\t]%c", &c);
			printf("%c ", c);
			g->bricks[i*14+j].enabled = 1;
			g->bricks[i*14+j].value = c-'0';

			switch(c)
			{
			case '1':
				g->bricks[i*14+j].s = sprite_init(45+j*50+j, 45+i*20+i, 50, 20, (alt_u32*) TEXTURES_BASE+TEXTURE_BRICK0, 50, 0);
				break;
			case '2':
				g->bricks[i*14+j].s = sprite_init(45+j*50+j, 45+i*20+i, 50, 20, (alt_u32*) TEXTURES_BASE+TEXTURE_BRICK1, 50, 0);
				break;
			case '3':
				g->bricks[i*14+j].s = sprite_init(45+j*50+j, 45+i*20+i, 50, 20, (alt_u32*) TEXTURES_BASE+TEXTURE_BRICK2, 50, 0);
				break;
			case '4':
				g->bricks[i*14+j].s = sprite_init(45+j*50+j, 45+i*20+i, 50, 20, (alt_u32*) TEXTURES_BASE+TEXTURE_BRICK3, 50, 0);
				break;
			case '*':
				g->bricks[i*14+j].enabled = 0;
				break;
			}

			buffer += read+1;
		}
		printf("\n");
	}

	// Initialize paddle
	g->paddle = sprite_init(300,440, 200, 20, (alt_u32*) TEXTURES_BASE+TEXTURE_PADDLE, 100, 0);

	// Initialize ball
	g->balls[0].s = sprite_init(g->paddle->x+100,g->paddle->y-20, 20,20, (alt_u32*) TEXTURES_BASE+IMG_BALL, 0, 0x2a2a2a);
	g->balls[0].v.x = 1;
	g->balls[0].v.y = -1;
	g->balls[0].enabled = 1;

	g->balls[1].s = sprite_init(g->paddle->x+100,g->paddle->y-20, 20,20, (alt_u32*) TEXTURES_BASE+IMG_BALL, 0, 0x2a2a2a);
	g->balls[1].v.x = 1;
	g->balls[1].v.y = -1;
	g->balls[1].enabled = 0;

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

	// Display background
	sprite * s = sprite_init(0,0, 800, 480, (alt_u32*) display->frame_buffer[0], 0, 0);
	display_add_sprite(display, s, 0);
	free(s);

	// Display walls
	for(i=0; i<3; i++)
		display_add_sprite(display, g->walls[i], 0);

	// Display bricks
	for(i=0; i< 14; i++)
		for(j=0; j< 12; j++)
			if(g->bricks[i*12+j].enabled) display_add_sprite(display, g->bricks[i*12+j].s, 0);

	// Display ball
	if(g->balls[0].enabled) display_add_sprite(display, g->balls[0].s, 0);
	if(g->balls[1].enabled) display_add_sprite(display, g->balls[1].s, 0);

	// Display paddle
	display_add_sprite(display, g->paddle, 1);

	g->state = NOT_MOVING;
}
