/*
 * player2.c
 *
 *  Created on: 29 mars 2015
 *      Author: Nicolas
 */

#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <includes.h>
#include <alt_types.h>

#include "pic32.h"
#include "rpc.h"
#include "mpack.h"
#include "breakout.h"
#include "alt_video_display.h"
#include "simple_graphics.h"
#include "touch_spi.h"

void player2_task(void* pdata)
{
	game_state * game = (game_state *) pdata;

	game->lcd_handle = lcd_init(LCD_BASE, LCD_RESET_N_BASE);
	// init touch
	TOUCH_HANDLE *pTouch;
	pTouch = Touch_Init(TOUCH_SPI_BASE, TOUCH_PEN_IRQ_N_BASE, TOUCH_PEN_IRQ_N_IRQ);
	if (!pTouch)	 printf("Failed to init touch\r\n");
	else			 printf("Init touch successfully\r\n");




	alt_video_display * Display;
	Display->interlace = 0;
	Display->bytes_per_pixel = 2;
	Display->color_depth = 16;
	Display->height = SCREEN_HEIGHT;
	Display->width = SCREEN_WIDTH;




	lcd_clear(game->lcd_handle, 0);

		// draw boxes
	  vid_draw_box (game->lcd_handle,0,0, 120, 110, RED_16, 1, Display);
	  vid_draw_box (game->lcd_handle,121,0, 240, 110, BLUE_16, 1, Display);
	  vid_draw_box (game->lcd_handle,0,111, 120, 220, INDIGO_16, 1, Display);
	  vid_draw_box (game->lcd_handle,121,111, 240, 220, 0x07E0, 1, Display);
	  vid_draw_box (game->lcd_handle,0,221, 240,256, 0xFFE0 , 1, Display);
	  vid_draw_box (game->lcd_handle,0,257, 120, 320,0x0F0F , 1, Display);
	  vid_draw_box (game->lcd_handle,121,257, 240, 320, 0x0F0F , 1, Display);




	   // add title to boxes
	  vid_print_string_alpha(game->lcd_handle,21 ,40 ,0xFFFFFF ,RED_16, tahomabold_20, Display, "Life +1");
	  vid_print_string_alpha(game->lcd_handle,141 ,40 ,0xFFFFFF ,BLUE_16, tahomabold_20, Display, "Brick +1");
	  vid_print_string_alpha(game->lcd_handle,21 ,135 ,0xFFFFFF ,INDIGO_16, tahomabold_20, Display, "Larger/ \nsmaller");
	  vid_print_string_alpha(game->lcd_handle,141 ,150 ,0xFFFFFF ,0x07E0 , tahomabold_20, Display, "ball +1");
	  vid_print_string_alpha(game->lcd_handle,40,225,0x0 , 0xFFE0 , tahomabold_20, Display, "slower / faster");
	  vid_print_string_alpha(game->lcd_handle,40,275,0x0 , 0x0F0F , tahomabold_20, Display, " - ");
	  vid_print_string_alpha(game->lcd_handle,175,275,0x0 , 0x0F0F , tahomabold_20, Display, "+");
	  vid_draw_line(game->lcd_handle,120,256, 120, 320, 64, 0x0,Display);
	  vid_draw_line(game->lcd_handle,0,256, 240, 256, 240, 0x0,Display);
	  vid_draw_line(game->lcd_handle,0,110, 240, 110, 240, 0x0,Display);
	  vid_draw_line(game->lcd_handle,0,220, 240, 220, 240, 0x0,Display);

	int pX = 0, pY = 0;
	while (1)
	{

		if (Touch_GetXY(pTouch, &pX, &pY)){
					POINT point;
					PtSet(&point, pX, pY);

					//left right top bottom
					RECT life = {0, 120, 0, 110};
					RECT brick = {121, 240, 0, 110};
					RECT ls = {0, 120, 111, 220};
					RECT ball = {121, 240, 110, 220};
					RECT plus = {121,257, 240, 320};
					RECT moins = {0,257, 120, 320};


					if(IsPtInRect(&point, &life))
					{
						printf( "LIFE +1\n " );
						OSTimeDlyHMSM(0, 0, 0, 200);
					}
					else if(IsPtInRect(&point, &brick))
					{
						printf( "Brick +1\n");
						OSTimeDlyHMSM(0, 0, 0, 200);
					}
					else if(IsPtInRect(&point, &ls))
					{
						printf( "Larger / Smaller\n");
						OSTimeDlyHMSM(0, 0, 0, 200);
					}
					else if(IsPtInRect(&point, &ball))
					{
						printf( "Ball +1\n");
						OSTimeDlyHMSM(0, 0, 0, 200);

					}
					else if(IsPtInRect(&point, &plus))
					{
						printf( "faster \n");
						OSTimeDlyHMSM(0, 0, 0, 200);

					}
					else if(IsPtInRect(&point, &moins))
					{
						printf( "slower \n");
						OSTimeDlyHMSM(0, 0, 0, 200);

					}



					Touch_EmptyFifo(pTouch);
				}
	}
}
