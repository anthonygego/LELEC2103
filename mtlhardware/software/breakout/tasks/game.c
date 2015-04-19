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

void game_task(void* pdata)
{
	game_struct * game = (game_struct*) pdata;
	display_info * display = game->display_handle;
	adxl345_coordinates adxl_c = {0,0,0};
	alt_u8 mtc_event = 0, mtc_touchnum = 0;
	alt_u16 mtc_x1 = 0, mtc_x2 = 0, mtc_y1 = 0, mtc_y2 = 0;
	alt_16 adxl_mean = 0, mtc_mean = 300;
	int delta, j, accel_x = 300;
	char text[200];

	while(1)
	{
		//
		// Compute new coordinate for the paddle from accelerometer data
		//

		alt_u8 double_click = 0;

		if(game->state != NOGAME && game->controller) {
			adxl345_read(game->adxl345_handle, ADXL345_DATAX0, (alt_u8 *)  &adxl_c, 6);
			adxl_mean = abs(adxl_c.y) <= 255 ? adxl_c.y/5 + 4*adxl_mean/5 : adxl_mean;

			accel_x = (-adxl_mean*32/10)+400-game->paddle.width/2;
			accel_x = (accel_x > 800-game->paddle.width) ? 800-game->paddle.width : (accel_x < 0) ? 0 : accel_x;
		}
		else if(game->state != NOGAME && mtc_get_status(game->mtc_handle, &mtc_event, &mtc_touchnum, &mtc_x1, &mtc_y1, &mtc_x2, &mtc_y2)){
			if(mtc_y1 > 440 && mtc_y1 < 480) {
				mtc_mean = (mtc_x1- game->paddle.width/2)/5 + 4*mtc_mean/5;
				accel_x = (mtc_mean > 800-game->paddle.width) ? 800-game->paddle.width : (mtc_mean < 0) ? 0 : mtc_mean;
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
			if(double_click || mtc_get_status(game->mtc_handle, &mtc_event, &mtc_touchnum, &mtc_x1, &mtc_y1, &mtc_x2, &mtc_y2))
				if(double_click || (mtc_event == MTC_ST_DOUBLECLICK && mtc_y1 < 440))
					game->state = PAUSED;

			// Pop event queue
			breakout_event_pop(game);

			// Update paddle and ball position
			display_move_sprite(display, &game->paddle, accel_x, 440);

			alt_16 new_ball_x = game->ball.s.x + game->ball.v.x*game->speed;
			alt_16 new_ball_y = game->ball.s.y + game->ball.v.y*game->speed;

			// Collision with paddle
			if(breakout_ball_collision(game->ball, game->paddle, &new_ball_x, &new_ball_y))
				breakout_ball_paddle(&game->ball, game->paddle);

			// Check for collision with walls
			if(new_ball_y < 10) {
				game->ball.v.y *= -1;
				new_ball_y = 10;
				display_move_sprite(display, &game->ball.s, new_ball_x, new_ball_y);
			}
			else if(new_ball_x > DISPLAY_MAX_WIDTH - 10 - BALL_WIDTH || new_ball_x < 10) {
				game->ball.v.x *= -1;
				new_ball_x = new_ball_x < 10 ? 10 : 770;
				display_move_sprite(display, &game->ball.s, new_ball_x, new_ball_y);
			}
			else if(new_ball_y + BALL_HEIGHT > DISPLAY_MAX_HEIGHT)
			{
				// Out of game
				game->state = NOT_MOVING;

				if(--(game->lives) <= 0)
				{
					game->state = LOST;
					sprintf(text, "You loose !\nScore : %d", (int) game->score);
					display_add_text(display, 300, 170, 0xffffff, tahomabold_32, text);
					display_remove_sprite(display, game->ball.s);
					display_move_sprite(display, &game->paddle, 300, game->paddle.y);
					display_remove_sprite(display, game->paddle);
				}
				else
					printf("Lost ball ! Remaining lives : %d\n", game->lives);

				display_move_sprite(display, &game->ball.s, game->paddle.x+game->paddle.width/2, game->paddle.y-20);
				display_end_frame(display);

			}
			else
			{
				alt_u8 collision = 0;
				for(j=0; j<NBR_BRICKS && !collision; j++) {
					if(game->bricks[j].enabled) {
						alt_u8 collision_from = breakout_ball_collision(game->ball, game->bricks[j].s, &new_ball_x, &new_ball_y);
						if(collision_from) {
							// Collision with brick
							game->score += SCORE_UNIT*game->lives;
							collision = 1;

							display_remove_sprite(display, game->bricks[j].s);

							new_ball_x = game->ball.s.x;
							new_ball_y = game->ball.s.y;

							// Compute new vector
							if(collision_from == 1 || collision_from == 3) // left
								game->ball.v.x *= -1;
							else
								game->ball.v.y *= -1;

							if(game->bricks[j].value == 1) {
								game->rbricks--;
								game->bricks[j].enabled = 0;
							}
							else {
								// Replace brick
								game->bricks[j].s.img_base = display->bricks_img[game->bricks[j].value-2];
								game->bricks[j].value--;
								display_add_sprite(display, game->bricks[j].s);
							}

							display_end_frame(display);
						}
					}
				}

				if(game->rbricks == 0) {
					game->state = WON;
					sprintf(text, "You win !\nScore : %d", (int) game->score);
					display_add_text(display, 300, 170, 0xffffff, tahomabold_32, text);
					display_remove_sprite(display, game->ball.s);
					display_move_sprite(display, &game->paddle, 300, game->paddle.y);
					display_remove_sprite(display,game->paddle);
					display_end_frame(display);
				}

				display_move_sprite(display, &game->ball.s, new_ball_x, new_ball_y);
			}

			break;
		//
		// IF BALL IS NOT MOVING
		//
		case NOT_MOVING:
			// If a double click is done, launch the ball(s)
			if(double_click || mtc_get_status(game->mtc_handle, &mtc_event, &mtc_touchnum, &mtc_x1, &mtc_y1, &mtc_x2, &mtc_y2))
				if(double_click || (mtc_event == MTC_ST_DOUBLECLICK && mtc_y1 < 440))
					game->state = BALL_MOVING;

			// Update paddle and balls position
			delta = accel_x - game->paddle.x;
			display_move_sprite(display, &game->ball.s, game->ball.s.x + delta, game->ball.s.y);
			display_move_sprite(display, &game->paddle, accel_x, 440);

			break;
		//
		// IF GAME IS PAUSED
		//
		case PAUSED:
			// If a double click is done, launch the ball(s)
			if(double_click || mtc_get_status(game->mtc_handle, &mtc_event, &mtc_touchnum, &mtc_x1, &mtc_y1, &mtc_x2, &mtc_y2))
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
