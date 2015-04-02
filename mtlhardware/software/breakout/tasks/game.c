#include <io.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <unistd.h>
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
		alt_8 brick_placed = 0;
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
		case ADD_BRICK:
			if(g->rbricks == 167)
				break;

			while(!brick_placed)
			{
				alt_32 rnd = rand() % NBR_BRICKS;
				if(!g->bricks[rnd].enabled && !sprite_collision(g->ball.s->x, g->ball.s->y, g->ball.s->width, g->ball.s->height, g->ball.s->img_base,
						g->bricks[rnd].s->x, g->bricks[rnd].s->y, g->bricks[rnd].s->width, g->bricks[rnd].s->height, g->bricks[rnd].s->img_base))
				{
					g->bricks[rnd].enabled = 1;
					g->bricks[rnd].value = rand()%4 + 1;

					g->bricks[rnd].s = sprite_init(45+(rnd%14)*50+(rnd%14), 45+(rnd/14)*20+(rnd/14), 50, 20, (alt_u32*) TEXTURES_BASE+TEXTURE_BRICK0+(g->bricks[rnd].value-1)*TEXTURE_BRICK_SIZE, 50, 0);
					g->rbricks++;

					display_add_sprite(g->periph.display_handle, g->bricks[rnd].s, 0);
					brick_placed = 1;
				}
			}

			break;
		case SPEED_DOWN:
			g->speed = (g->speed > 15) ? g->speed - 5 : 10;
			break;
		case SPEED_UP:
			g->speed = (g->speed <= 20) ? g->speed + 5 : 20;
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
	int delta, j;
	alt_16 adxl_mean = 0;

	while(1)
	{
		//
		// Compute new coordinate for the paddle from accelerometer data
		//
		adxl345_read(game->periph.adxl345_handle, ADXL345_DATAX0, (alt_u8 *)  &adxl_c, 6);
		adxl_mean = abs(adxl_c.y) <= 255 ? adxl_c.y/5 + 4*adxl_mean/5 : adxl_mean;

		int accel_x = (-adxl_mean*32/10)+400-game->paddle->width/2;
		accel_x = (accel_x > 800-game->paddle->width) ? 800-game->paddle->width : (accel_x < 0) ? 0 : accel_x;

		//
		// Main Game logic
		//
		switch(game->state)
		{
		case BALL_MOVING:

			// If a double click is done, launch the ball(s)
			if(mtc_get_status(game->periph.mtc_handle, &mtc_event, &mtc_touchnum, &mtc_x1, &mtc_y1, &mtc_x2, &mtc_y2))
				if(mtc_event == MTC_ST_DOUBLECLICK)
					game->state = PAUSED;

			// Pop event queue
			game_event_pop(game);

			// Update paddle and balls position
			display_move_sprite(display, game->paddle, 0, accel_x, 440);

			alt_u16 ball_new_x = game->ball.s->x + game->ball.v.x*game->speed;
			alt_u16 ball_new_y = game->ball.s->y + game->ball.v.y*game->speed;

			// Check for collision with walls and paddle
			for(j=0; j<3; j++)
			{
				if(sprite_collision(ball_new_x, ball_new_y, game->ball.s->width, game->ball.s->height, game->ball.s->img_base,
						game->walls[j]->x, game->walls[j]->y, game->walls[j]->width, game->walls[j]->height, game->walls[j]->img_base))
				{
					if((j+1)%2==0)
						game->ball.v.y *= -1;
					else
						game->ball.v.x *= -1;
				}
			}


			if(sprite_collision(ball_new_x, ball_new_y, game->ball.s->width, game->ball.s->height, game->ball.s->img_base,
					game->paddle->x, game->paddle->y, game->paddle->width, game->paddle->height, game->paddle->img_base))
			{
				// Collision with paddle
				game->ball.v.y *= -1;
			}

			if(ball_new_x + BALL_WIDTH > DISPLAY_MAX_WIDTH || ball_new_y + BALL_HEIGHT > DISPLAY_MAX_HEIGHT)
			{
				// Out of game
				game->state = NOT_MOVING;
				display_move_sprite(display, game->ball.s, 1, game->paddle->x+game->paddle->width/2, game->paddle->y-20);

				if(--(game->lives) <= 0)
				{
					game->state = LOST;
					printf("Game over (score :%d) !\n", (int) game->score);
					breakout_clear_screen(display);
				}
				else
					printf("Lost ball ! Remaining lives : %d\n", game->lives);
				break;
			}
			else
			{
				alt_u8 collision = 0;

				for(j=0; j<NBR_BRICKS && !collision; j++)
				{

					if(game->bricks[j].enabled)
					{
						alt_u8 collision_from = sprite_collision(ball_new_x, ball_new_y, game->ball.s->width, game->ball.s->height, game->ball.s->img_base,
								game->bricks[j].s->x, game->bricks[j].s->y, game->bricks[j].s->width, game->bricks[j].s->height, game->bricks[j].s->img_base);

						if(collision_from)
						{
							// Collision with brick
							game->score += SCORE_UNIT;
							collision = 1;

							display_remove_sprite(display, game->bricks[j].s, 0);

							if(game->bricks[j].value == 1)
							{
								game->rbricks--;
								game->bricks[j].enabled = 0;

								free(game->bricks[j].s);
							}
							else
							{
								// Replace brick
								game->bricks[j].s->img_base = (alt_u32*) TEXTURES_BASE+TEXTURE_BRICK0+(game->bricks[j].value-2)*TEXTURE_BRICK_SIZE;
								game->bricks[j].value--;
								display_add_sprite(display, game->bricks[j].s, 0);
							}

							// Compute new vector
							if(collision_from == 1) // horizontal
								game->ball.v.x *= -1;
							else // vertical
								game->ball.v.y *= -1;
						}
					}
				}


				if(game->rbricks == 0)
				{
					game->state = WON;
					printf("Well done (score :%d) !\n", (int) game->score);
					breakout_clear_screen(display);
					break;
				}

				ball_new_x = game->ball.s->x + game->ball.v.x*game->speed;
				ball_new_y = game->ball.s->y + game->ball.v.y*game->speed;

				display_move_sprite(display, game->ball.s, 1, ball_new_x, ball_new_y);
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
			display_move_sprite(display, game->ball.s, 0, (game->ball.s->x) + delta, game->ball.s->y);
			display_move_sprite(display, game->paddle, 1, accel_x, 440);

			usleep(20000);
			break;
		case PAUSED:
			// If a double click is done, launch the ball(s)
			if(mtc_get_status(game->periph.mtc_handle, &mtc_event, &mtc_touchnum, &mtc_x1, &mtc_y1, &mtc_x2, &mtc_y2))
				if(mtc_event == MTC_ST_DOUBLECLICK)
					game->state = BALL_MOVING;
			break;
		default:
			break;
		}

		//
		// Sleep for a while
		//
		OSTimeDlyHMSM(0, 0, 0, 40);
	}
}


void game_status_task(void* pdata)
{
	game_struct * game = (game_struct*) pdata;

	while(1)
	{
		char buffer[1024];
		mpack_writer_t writer;
		mpack_writer_init_buffer(&writer, buffer, sizeof(buffer));

		mpack_start_map(&writer, 6);

		// Game state
		mpack_write_cstr(&writer, "state");
		mpack_write_i32(&writer, game->state);

		// Game state
		mpack_write_cstr(&writer, "lives");
		mpack_write_i32(&writer, game->lives);

		// Game state
		mpack_write_cstr(&writer, "bricks");
		mpack_write_i32(&writer, game->rbricks);

		// Game state
		mpack_write_cstr(&writer, "padsize");
		mpack_write_i32(&writer, game->paddle->width);

		// Game state
		mpack_write_cstr(&writer, "speed");
		mpack_write_i32(&writer, game->speed);

		// Game state
		mpack_write_cstr(&writer, "score");
		mpack_write_i32(&writer, game->score);

		mpack_finish_map(&writer);

		// clean up
		size_t count = mpack_writer_buffer_used(&writer);
		mpack_writer_destroy(&writer);

		pic32_sendrpc(game->periph.pic32_handle, buffer, count, CYCLONE_RPC_INFO);


		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}
