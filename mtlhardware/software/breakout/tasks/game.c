#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <includes.h>
#include <alt_types.h>
#include <sys/alt_cache.h>

#include "pic32.h"
#include "mtc.h"
#include "display.h"
#include "rpc.h"
#include "mpack.h"
#include "breakout.h"
#include "sprite.h"

alt_u8 sprite_collision(alt_u16 x1, alt_u16 y1, alt_u16 w1, alt_u16 h1, alt_u32* base1, alt_u16 x2, alt_u16 y2, alt_u16 w2, alt_u16 h2, alt_u32* base2)
{
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

void game_event_pop(game_struct * g)
{
	alt_u8 err;

	// Treat an event if queue is not empty
	OSSemPend(g->events_queue->sem, 0, &err);
	//
	if(!queue_is_empty(g->events_queue))
	{

		game_event event = queue_pop(g->events_queue);
		printf("Popping event : %d\n", event);
		switch(event)
		{
		case ADD_LIFE:
			g->lives++;
			break;
		case REMOVE_LIFE:
			g->lives--;
			break;
		case SWITCH_PADDLE_SIZE:
			display_remove_sprite(g->periph.display_handle, g->paddle, 0);
			g->paddle->width = (g->paddle->width == 200) ? 100 : 200;
			display_add_sprite(g->periph.display_handle, g->paddle, 0);
			break;
		case ADD_BALL:
			g->balls[1].enabled = 0;
			break;
		case SPEED_DOWN:
			g->speed = (g->speed > 10) ? g->speed - 5 : 5;
			break;
		case SPEED_UP:
			g->speed = (g->speed <= 50) ? g->speed + 5 : 50;
			break;
		default:
			break;
		}

	}
	OSSemPost(g->events_queue->sem);
}

void game_task(void* pdata)
{
	game_struct * game = (game_struct*) pdata;
	display_info * display = game->periph.display_handle;
	adxl345_coordinates adxl_c;
	alt_u8 mtc_event, mtc_touchnum;
	alt_u16 mtc_x1, mtc_x2, mtc_y1, mtc_y2;
	int delta, i;

	while(1)
	{
		//
		// Compute new coordinate for the paddle from accelerometer data
		//
		adxl345_read(game->periph.adxl345_handle, ADXL345_DATAX0, (alt_u8 *)  &adxl_c, 6);
		int accel_x = (-adxl_c.y*600/400)+300;
		accel_x = (accel_x > 600) ? 600 : (accel_x < 0) ? 0 : accel_x;

		//
		// Main Game logic
		//
		switch(game->state)
		{
		case NOGAME:
			break;
		case BALL_MOVING:

			// Pop event queue
			game_event_pop(game);

			// Update paddle and balls position
			delta = accel_x - game->paddle->x;
			if(abs(delta) > 10)
				display_move_sprite(display, game->paddle, 0, accel_x, 440);

			for(i=0; i<2; i++)
			{
				alt_u16 ball_new_x = game->balls[i].s->x + game->balls[i].v.x*game->speed;
				alt_u16 ball_new_y = game->balls[i].s->y + game->balls[i].v.y*game->speed;

				// Check for collision with walls and paddle
				if(sprite_collision(ball_new_x, ball_new_y, game->balls[i].s->width, game->balls[i].s->height, game->balls[i].s->img_base,
						game->walls[0]->x, game->walls[0]->y, game->walls[0]->width, game->walls[0]->height, game->walls[0]->img_base))
				{
					// Collision with wall 1
					game->balls[i].v.x = - game->balls[i].v.x;
				}
				else if(sprite_collision(ball_new_x, ball_new_y, game->balls[i].s->width, game->balls[i].s->height, game->balls[i].s->img_base,
						game->walls[1]->x, game->walls[1]->y, game->walls[1]->width, game->walls[1]->height, game->walls[1]->img_base))
				{
					// Collision with wall 2
					game->balls[i].v.y = - game->balls[i].v.y;
				}
				else if(sprite_collision(ball_new_x, ball_new_y, game->balls[i].s->width, game->balls[i].s->height, game->balls[i].s->img_base,
						game->walls[2]->x, game->walls[2]->y, game->walls[2]->width, game->walls[2]->height, game->walls[2]->img_base))
				{
					// Collision with wall 3
					game->balls[i].v.x = - game->balls[i].v.x;
				}
				else if(sprite_collision(ball_new_x, ball_new_y, game->balls[i].s->width, game->balls[i].s->height, game->balls[i].s->img_base,
						game->paddle->x, game->paddle->y, game->paddle->width, game->paddle->height, game->paddle->img_base))
				{
					// Collision with paddle
					game->balls[i].v.y = - game->balls[i].v.y;
				}
				else if(ball_new_x + BALL_WIDTH > DISPLAY_MAX_WIDTH || ball_new_y + BALL_HEIGHT > DISPLAY_MAX_HEIGHT)
				{
					// Out of game
					if(game->balls[0].enabled + game->balls[1].enabled < 2)
					{
						game->state = NOT_MOVING;
						display_move_sprite(display, game->balls[0].s, 1, game->paddle->x+game->paddle->width/2, game->paddle->y-20);

						if(--(game->lives) <= 0)
						{
							game->state = NOGAME;
							printf("Game over (score :%d) !\n", (int) game->score);
							breakout_clear_screen(display);
						}
						else
							printf("Lost ball ! Remaining lives : %d\n", game->lives);
						break;
					}
					else
					{
						display_remove_sprite(display, game->balls[1].s, 1);
						game->balls[1].enabled = 0;
						break;
					}
				}

				alt_u8 collision = 0;
				alt_u16 j;
				for(j=0; j<NBR_BRICKS && !collision; j++)
				{

					if(game->bricks[j].enabled)
					{
						alt_u8 collision_from = sprite_collision(ball_new_x, ball_new_y, game->balls[i].s->width, game->balls[i].s->height, game->balls[i].s->img_base,
								game->bricks[j].s->x, game->bricks[j].s->y, game->bricks[j].s->width, game->bricks[j].s->height, game->bricks[j].s->img_base);

						if(collision_from)
						{
							// Collision with brick
							game->score += SCORE_UNIT;
							collision = 1;

							display_remove_sprite(display, game->bricks[j].s, 0);

							if(game->bricks[j].value == 1)
								game->bricks[j].enabled = 0;
							else
							{
								// Replace brick
								sprite * new_sprite = sprite_init(game->bricks[j].s->x, game->bricks[j].s->y, game->bricks[j].s->width,
										game->bricks[j].s->height, (alt_u32*) TEXTURES_BASE+TEXTURE_BRICK0+(game->bricks[j].value-2)*TEXTURE_BRICK_SIZE, 50, 0);

								free(game->bricks[j].s);
								game->bricks[j].s = new_sprite;
								game->bricks[j].value--;
								display_add_sprite(display, game->bricks[j].s, 0);
							}

							// Compute new vector
							if(collision_from == 1) // horizontal
								game->balls[i].v.x = - game->balls[i].v.x;
							else // vertical
								game->balls[i].v.y = - game->balls[i].v.y;
						}
					}
				}

				ball_new_x = game->balls[i].s->x + game->balls[i].v.x*game->speed;
				ball_new_y = game->balls[i].s->y + game->balls[i].v.y*game->speed;

				if(game->balls[i].enabled)
					display_move_sprite(display, game->balls[0].s, 1, ball_new_x, ball_new_y);
			}

			break;
		//
		// IF BALL IS NOT MOVING
		//
		case NOT_MOVING:
			// If a double click is done, launch the ball(s)
			if(mtc_get_status(game->periph.mtc_handle, &mtc_event, &mtc_touchnum, &mtc_x1, &mtc_y1, &mtc_x2, &mtc_y2))
				if(mtc_event == MTC_ST_DOUBLECLICK)
					game->state = BALL_MOVING;

			// Update paddle and balls position
			delta = accel_x - game->paddle->x;
			if(abs(delta) > 10)
			{
				if(game->balls[0].enabled)
					display_move_sprite(display, game->balls[0].s, 0, (game->balls[0].s->x) + delta, game->balls[0].s->y);
				if(game->balls[1].enabled)
					display_move_sprite(display, game->balls[1].s, 0, (game->balls[1].s->x) + delta, game->balls[1].s->y);
				display_move_sprite(display, game->paddle, 1, accel_x, 440);
			}

			break;
		case PAUSED:
			break;
		default:
			break;
		}

		//
		// Sleep for a while
		//
		OSTimeDlyHMSM(0, 0, 0, 30);
	}
}
