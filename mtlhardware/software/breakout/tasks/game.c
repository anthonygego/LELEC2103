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
#include "tasks.h"
#include "display.h"
#include "mpack.h"
#include "breakout.h"
#include "simpletext.h"

void game_event_pop(game_struct * g)
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
				if(!g->bricks[rnd].enabled && !breakout_collision(g->ball.s, g->bricks[rnd].s))
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
			g->speed = (g->speed > 9) ? g->speed - 1 : 5;
			break;
		case SPEED_UP:
			g->speed = (g->speed <= 10) ? g->speed + 1 : 10;
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
	alt_16 adxl_mean = 0, mtc_mean = 300;
	int delta, j, accel_x = 300;
	char text[200];

	while(1)
	{
		//
		// Compute new coordinate for the paddle from accelerometer data
		//
		alt_u8 double_click = 0;
		if(game->controller) {
			adxl345_read(game->periph.adxl345_handle, ADXL345_DATAX0, (alt_u8 *)  &adxl_c, 6);
			adxl_mean = abs(adxl_c.y) <= 255 ? adxl_c.y/5 + 4*adxl_mean/5 : adxl_mean;

			accel_x = (-adxl_mean*32/10)+400-game->paddle->width/2;
			accel_x = (accel_x > 800-game->paddle->width) ? 800-game->paddle->width : (accel_x < 0) ? 0 : accel_x;
		}
		else if(mtc_get_status(game->periph.mtc_handle, &mtc_event, &mtc_touchnum, &mtc_x1, &mtc_y1, &mtc_x2, &mtc_y2)){
			if(mtc_y1 > 440) {
				mtc_mean = (mtc_x1-50)/5 + 4*mtc_mean/5;
				accel_x = (mtc_mean > 800-game->paddle->width) ? 800-game->paddle->width : (mtc_mean < 0) ? 0 : mtc_mean;
			}
			else if(mtc_event == MTC_ST_DOUBLECLICK && mtc_y1 < 430) {
				double_click = 1;
			}
		}


		//
		// Main Game logic
		//
		switch(game->state)
		{
		case BALL_MOVING:

			// If a double click is done, launch the ball(s)
			if(double_click || mtc_get_status(game->periph.mtc_handle, &mtc_event, &mtc_touchnum, &mtc_x1, &mtc_y1, &mtc_x2, &mtc_y2))
				if(double_click || (mtc_event == MTC_ST_DOUBLECLICK && mtc_y1 < 440))
					game->state = PAUSED;

			// Pop event queue
			game_event_pop(game);

			// Update paddle and balls position
			display_move_sprite(display, game->paddle, accel_x, 440);

			alt_u16 ball_new_x = game->ball.s->x + game->ball.v.x*game->speed;
			alt_u16 ball_new_y = game->ball.s->y + game->ball.v.y*game->speed;

			display_move_sprite(display, game->ball.s, ball_new_x, ball_new_y);

			// Check for collision with walls and paddle
			for(j=0; j<3; j++)
			{
				if(breakout_collision(game->ball.s, game->walls[j]))
				{
					if((j+1)%2==0)
						game->ball.v.y *= -1;
					else
						game->ball.v.x *= -1;
				}
			}


			if(breakout_collision(game->ball.s, game->paddle))
			{
				// Collision with paddle
				game->ball.v.y *= -1;
			}

			if(ball_new_x + BALL_WIDTH > DISPLAY_MAX_WIDTH || ball_new_y + BALL_HEIGHT > DISPLAY_MAX_HEIGHT)
			{
				// Out of game
				game->state = NOT_MOVING;
				display_move_sprite(display, game->ball.s, game->paddle->x+game->paddle->width/2, game->paddle->y-20);

				if(--(game->lives) <= 0)
				{
					game->state = LOST;
					sprintf(text, "You loose !\nScore : %d", (int) game->score);
					display_add_text(display, 300, 170, 0xffffff, tahomabold_32, 0, text);
					display_remove_sprite(display, game->ball.s);
					display_move_sprite(display, game->paddle, 300, game->paddle->y);
					display_remove_sprite(display, game->paddle);
				}
				else
					printf("Lost ball ! Remaining lives : %d\n", game->lives);

				display_end_frame(display);

			}
			else
			{
				alt_u8 collision = 0;
				for(j=0; j<NBR_BRICKS && !collision; j++) {
					if(game->bricks[j].enabled) {
						alt_u8 collision_from = breakout_collision(game->ball.s, game->bricks[j].s);
						if(collision_from) {
							// Collision with brick
							game->score += SCORE_UNIT;
							collision = 1;

							display_remove_sprite(display, game->bricks[j].s);

							if(game->bricks[j].value == 1) {
								game->rbricks--;
								game->bricks[j].enabled = 0;

								free(game->bricks[j].s);
							}
							else {
								// Replace brick
								game->bricks[j].s->img_base = display->bricks_img[game->bricks[j].value-2];
								game->bricks[j].value--;
								display_add_sprite(display, game->bricks[j].s);
							}


							// Compute new vector
							if(collision_from == 1) // horizontal
								game->ball.v.x *= -1;
							else // vertical
								game->ball.v.y *= -1;

							display_end_frame(display);
						}
					}
				}

				if(game->rbricks == 0) {
					game->state = WON;
					sprintf(text, "You win !\nScore : %d", (int) game->score);
					display_add_text(display, 300, 170, 0xffffff, tahomabold_32, 0, text);
					display_remove_sprite(display, game->ball.s);
					display_move_sprite(display, game->paddle, 300, game->paddle->y);
					display_remove_sprite(display, game->paddle);
					display_end_frame(display);
				}

			}

			break;
		//
		// IF BALL IS NOT MOVING
		//
		case NOT_MOVING:
			// If a double click is done, launch the ball(s)
			if(double_click || mtc_get_status(game->periph.mtc_handle, &mtc_event, &mtc_touchnum, &mtc_x1, &mtc_y1, &mtc_x2, &mtc_y2))
				if(double_click || (mtc_event == MTC_ST_DOUBLECLICK && mtc_y1 < 440))
					game->state = BALL_MOVING;

			// Update paddle and balls position
			delta = accel_x - game->paddle->x;
			display_move_sprite(display, game->ball.s, (game->ball.s->x) + delta, game->ball.s->y);
			display_move_sprite(display, game->paddle, accel_x, 440);

			break;
		//
		// IF GAME IS PAUSED
		//
		case PAUSED:
			// If a double click is done, launch the ball(s)
			if(double_click || mtc_get_status(game->periph.mtc_handle, &mtc_event, &mtc_touchnum, &mtc_x1, &mtc_y1, &mtc_x2, &mtc_y2))
				if(double_click || (mtc_event == MTC_ST_DOUBLECLICK && mtc_y1 < 440))
					game->state = BALL_MOVING;
			break;
		default:
			break;
		}

		//
		// Sleep for a while
		//
		OSTimeDlyHMSM(0, 0, 0, 25);
	}
}
