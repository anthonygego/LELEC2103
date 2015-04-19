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
		else if(!strncmp(command, "NewGame", 7))
		{
			printf("Loading level : %d\n", atoi(command+8)%100);
			rpc_game_start(game, atoi(command+8));
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
		else
			printf("Unknown Command\n");
	}
}

