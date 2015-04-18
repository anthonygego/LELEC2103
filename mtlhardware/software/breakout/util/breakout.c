#include <io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <includes.h>
#include <sys/alt_cache.h>

#include "queue.h"
#include "breakout.h"
#include "simpletext.h"

void breakout_init_textures(game_struct * game)
{
	display_info * display = game->periph.display_handle;
	alt_u32 * textures;
	size_t len;
	alt_u8 err;
	int i,j;

	// Black background for cleaning screen
	for(i=0; i<800*480; i++)
		IOWR(display->frame_buffer[3], i, 0x0);

	// Clear screen and display loading message
	display_clear_screen(display);
	display_add_text(display, 175, 210, 0xffffff, tahomabold_32, 0, "Loading textures...");
	display_end_frame(display);

	// Create gradient background
	for(i=0; i<480; i++)
		for(j=0; j<800; j++)
			IOWR(display->frame_buffer[0], i*DISPLAY_MAX_WIDTH+j, 0xff0000 + ((i*255/480) << 8));

	// Loading ball, paddle and bricks textures from SD card
	OSSemPend(game->periph.pic32_handle->sem, 0, &err);
	pic32_sendrpc(game->periph.pic32_handle, "textures.bin", 13, CYCLONE_RPC_FILE);
	while(!pic32_receive(game->periph.pic32_handle, (char **) &textures, &len, 0));
	OSSemPost(game->periph.pic32_handle->sem);

	for(i=0; i<8000; i++)
		IOWR(TEXTURES_BASE, i, textures[i]);

	for(i=0; i<4000; i++)
		IOWR(display->bricks_img[0], i, textures[8000+i]);

	free(textures);

	// Creating wall textures
	for(i=0; i<4400; i++)
		IOWR(display->wall_vert_img, i,  i%3==0 ? 0x2a2a2a : 0x4a4a4a);

	for(i=0; i<8000; i++)
		IOWR(display->wall_horiz_img, i, i%3==0 ? 0x2a2a2a : 0x4a4a4a);

	// Display loading is finished
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

void breakout_ball_paddle(ball * ball, sprite * paddle)
{
	float ball_center_x = ball->s->x + ball->s->width/2;
	float paddle_center_x = paddle->x + paddle->width/2;
	float dist = ball_center_x - paddle_center_x;

	float speedx = ball->v.x;
	float speedy = ball->v.y;
	float speed = sqrt(speedx*speedx + speedy*speedy);

	speedx = speed * 0.9 * dist / (paddle->width/2);
	speedy = sqrt(speed*speed - speedx*speedx) * (speedy > 0? -1 : 1);

	speed = sqrt(speedx*speedx + speedy*speedy);
	if(abs(speed) > 0.05) {
		ball->v.x = speedx /speed;
		ball->v.y = speedy/speed;
	}
}

void breakout_init(game_struct * g, char * level, alt_8 controller)
{
	display_info * display = g->periph.display_handle;

	// Stop the game
	if(g->state != NOGAME)
		breakout_uninit(g);

	// Clear the screen and display loading message
	display_clear_screen(display);
	display_add_text(display, 250, 210, 0xffffff, tahomabold_32, 0, "Loading game...");
	display_end_frame(display);

	// Initialize bricks
	g->rbricks = 0;

	int i, j;
	for(i=0; i< 12; i++) {
		for(j=0; j < 14; level++) {
			g->bricks[i*14+j].enabled = 1;
			g->bricks[i*14+j].value = *level-'0';

			if(g->bricks[i*14+j].value > 0 && g->bricks[i*14+j].value < 5) {
				g->bricks[i*14+j].s = display_sprite_init(display, 45+j*50+j, 45+i*20+i, 50, 20, display->bricks_img[g->bricks[i*14+j].value-1], 0, 0);
				g->rbricks++;
				j++;
			}
			else if(*level == '*') {
				g->bricks[i*14+j].enabled = 0;
				j++;
			}
		}
	}

	// Initialize paddle
	g->paddle = display_sprite_init(display, 300,440, 200, 20, (alt_u32*) TEXTURES_BASE + IMG_PADDLE200, (alt_u8*) TEXTURES_BASE + ALPHA_PADDLE200*4, 1);

	// Initialize ball
	g->ball.s = display_sprite_init(display, g->paddle->x+100,g->paddle->y-20, 20,20, (alt_u32*) TEXTURES_BASE + IMG_BALL, (alt_u8*) TEXTURES_BASE + ALPHA_BALL*4, 2);
	g->ball.v.x = sqrt(2)/2;
	g->ball.v.y = -sqrt(2)/2;

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

	// Set controller
	g->controller = controller;

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

	// End software frame
	display_end_frame(display);

	// Display ball
	display_add_sprite(display, g->ball.s);

	// Display paddle
	display_add_sprite(display, g->paddle);

	g->state = NOT_MOVING;
}

alt_u8 breakout_ball_collision(ball *ball, sprite *s, alt_16 *new_ball_x, alt_16 *new_ball_y)
{
	alt_u8 result = 0;

	// Simple collision check
	if(!((*new_ball_x + ball->s->width < s->x) || (s->x + s->width < *new_ball_x) || (*new_ball_y + ball->s->height < s->y) || (s->y + s->height < *new_ball_y)))
	{
		// Enhanced collision check, taking alpha channel into account
		int i, j, collided = 0;
		for(i=0; i < ball->s->height && !collided; i++)
			for(j=0; j < ball->s->width && !collided; j++)
				if(!(s->alpha[i*ball->s->width+j]) && !((*new_ball_x+j+1 < s->x) || (s->x + s->width < *new_ball_x+j) || (*new_ball_y+i+1 < s->y) || (s->y + s->height < *new_ball_y+i)))
					collided = 1;

		if(collided)
		{
			float w = 0.5 * (ball->s->width + s->width);
			float h = 0.5 * (ball->s->height + s->height);
			float dx = (*new_ball_x+ball->s->width)/2 - (s->x+ball->s->width)/2;
			float dy = (*new_ball_y+ball->s->height)/2 - (s->y+ball->s->height)/2;

			float wy = w * dy;
			float hx = h * dx;

			if (wy > hx)
				if (wy > -hx)
					return 2;
				else
					return 1;
			else
				if (wy > -hx)
					return 3;
				else
					return 4;
		}
	}

	return result;
}

void breakout_event_pop(game_struct * g)
{
	alt_u8 err;
	display_info *display = g->periph.display_handle;

	// Treat an event if queue is not empty
	OSSemPend(g->events_queue->sem, 0, &err);
	if(!queue_is_empty(g->events_queue))
	{
		alt_8 brick_placed = 0;
		alt_u16 new_width;
		game_event event = queue_pop(g->events_queue);
		printf("Popping event : %d\n", event);
		switch(event)
		{
		case ADD_LIFE:
			g->lives++;
			break;
		case REMOVE_LIFE:
			if(g->lives > 1)
				g->lives--;
			break;
		case SWITCH_PADDLE_SIZE:
			new_width = (g->paddle->width == 200) ? 100 : 200;
			alt_u32 * new_base = (g->paddle->width == 200) ? (alt_u32*) TEXTURES_BASE + IMG_PADDLE100 : (alt_u32*) TEXTURES_BASE + IMG_PADDLE200;
			alt_u8 * new_alpha = (g->paddle->width == 200) ? (alt_u8*) TEXTURES_BASE + ALPHA_PADDLE100*4 : (alt_u8*) TEXTURES_BASE + ALPHA_PADDLE200*4;

			display_sprite_change(display, g->paddle, new_width, g->paddle->height, new_base, new_alpha);
			break;
		case ADD_BRICK:
			if(g->rbricks == 167)
				break;

			while(!brick_placed)
			{
				alt_32 rnd = rand() % NBR_BRICKS;
				if(!g->bricks[rnd].enabled && !breakout_ball_collision(&(g->ball), g->bricks[rnd].s, &(g->ball.s->x), &(g->ball.s->y)))
				{
					g->bricks[rnd].enabled = 1;
					g->bricks[rnd].value = rand()%4 + 1;

					g->bricks[rnd].s = display_sprite_init(display, 45+(rnd%14)*50+(rnd%14), 45+(rnd/14)*20+(rnd/14), 50, 20, display->bricks_img[g->bricks[rnd].value-1], 0, 0);
					g->rbricks++;

					display_add_sprite(display, g->bricks[rnd].s);
					brick_placed = 1;
					display_end_frame(display);
				}
			}

			break;
		case SPEED_DOWN:
			g->speed = (g->speed > 8) ? g->speed - 3 : 5;
			break;
		case SPEED_UP:
			g->speed = (g->speed <= 15) ? g->speed + 3 : 15;
			break;
		default:
			break;
		}

	}
	OSSemPost(g->events_queue->sem);
}
