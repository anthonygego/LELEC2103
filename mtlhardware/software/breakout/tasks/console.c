#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <string.h>
#include <includes.h>
#include <alt_types.h>
#include <sys/alt_stdio.h>

#include "pic32.h"
#include "mtc.h"
#include "adxl345.h"
#include "tasks.h"
#include "mpack.h"
#include "breakout.h"

void console_task(void* pdata)
{
	game_struct * game = (game_struct *) pdata;

	// Welcome message
	printf("Breakout console\n");

	while(1)
	{
		printf(">");

		char command[128];
		fgets(command, 128, stdin);

		if(!strncmp(command, "MyTest", 6))
		{
			printf("MyTest ok !\n");
		}
		else if(!strncmp(command, "MyGame", 6))
		{
			int level;
			printf("Enter a level :\n");
			scanf("%d", &level);

			rpc_game_start(game, level);
		}
		else if(!strncmp(command, "AddBrick", 8))
		{
			printf("Add brick\n");
			rpc_game_event(game, ADD_BRICK);
		}
		else if(!strncmp(command, "AddLife", 7))
		{
			printf("Add life\n");
			rpc_game_event(game, ADD_LIFE);
		}
		else if(!strncmp(command, "RemLife", 7))
		{
			printf("Remove life\n");
			rpc_game_event(game, REMOVE_LIFE);
		}
		else if(!strncmp(command, "SpeedUp", 7))
		{
			printf("Speed up\n");
			rpc_game_event(game, SPEED_UP);
		}
		else if(!strncmp(command, "SpeedDown", 9))
		{
			printf("Speed down\n");
			rpc_game_event(game, SPEED_DOWN);
		}
		else if(!strncmp(command, "PaddleSize", 10))
		{
			printf("Paddle size\n");
			rpc_game_event(game, SWITCH_PADDLE_SIZE);
		}
		else if(!strncmp(command, "MyMultiTouch", 12))
		{
			alt_u8 event, touchnum;
			alt_u16 x1,x2,y1,y2;

			if(mtc_get_status(game->mtc_handle, &event, &touchnum, &x1, &y1, &x2, &y2))
				if(touchnum == 2)
					printf("x1: %3d, y1: %3d\nx2: %3d, y2: %3d\nTouch num : %d\nEvent : 0x%X\n", x1, y1, x2, y2, touchnum, event);
				else
					printf("x1: %3d, y1: %3d\nTouch num : %d\nEvent : 0x%X\n", x1, y1, touchnum, event);
			else
				printf("No new point\n");
		}
		else if(!strncmp(command, "MyADXL", 6))
		{
			adxl345_coordinates c;
			adxl345_read(game->adxl345_handle, ADXL345_DATAX0, (alt_u8 *)  &c, 6);
			printf("X : %d - Y: %d, Z : %d\n", c.x, c.y, c.z);
		}
		else
			printf("Unknown Command\n");
	}
}

