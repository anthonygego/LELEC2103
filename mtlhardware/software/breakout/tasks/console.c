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
#include "console.h"
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
			char level_file[100];

			printf("Enter a level :\n");
			scanf("%d", &level);

			sprintf(level_file, "level%02d.txt", level);

			char * level_text;
			size_t len;

			pic32_sendrpc(game->periph.pic32_handle, level_file, 12, CYCLONE_RPC_FILE);
			while(!pic32_receive(game->periph.pic32_handle, &level_text, &len, 0));

			breakout_init(game, level_text);

			free(level_text);
		}else if(!strncmp(command, "AddBrick", 8))
		{
			printf("Add brick\n");
			alt_u8 err;
            OSSemPend(game->events_queue->sem, 0, &err);
			queue_push(game->events_queue, ADD_BRICK);
			OSSemPost(game->events_queue->sem);
		}else if(!strncmp(command, "AddLife", 7))
		{
			printf("Add life\n");
			alt_u8 err;
			OSSemPend(game->events_queue->sem, 0, &err);
			queue_push(game->events_queue, ADD_LIFE);
			OSSemPost(game->events_queue->sem);
		}else if(!strncmp(command, "RemLife", 7))
		{
			printf("Remove life\n");
			alt_u8 err;
		    OSSemPend(game->events_queue->sem, 0, &err);
			queue_push(game->events_queue, REMOVE_LIFE);
			OSSemPost(game->events_queue->sem);
		}else if(!strncmp(command, "SpeedUp", 7))
		{
			printf("Speed up\n");
			alt_u8 err;
			OSSemPend(game->events_queue->sem, 0, &err);
			queue_push(game->events_queue, SPEED_UP);
			OSSemPost(game->events_queue->sem);
		}else if(!strncmp(command, "SpeedDown", 9))
		{
			printf("Speed down\n");
			alt_u8 err;
			OSSemPend(game->events_queue->sem, 0, &err);
			queue_push(game->events_queue, SPEED_DOWN);
			OSSemPost(game->events_queue->sem);
		}else if(!strncmp(command, "PaddleSize", 10))
		{
			printf("Paddle size\n");
			alt_u8 err;
			OSSemPend(game->events_queue->sem, 0, &err);
			queue_push(game->events_queue, SWITCH_PADDLE_SIZE);
			OSSemPost(game->events_queue->sem);
		}else if(!strncmp(command, "MyMIWI", 6))
		{
			char buffer[256];
			mpack_writer_t writer;
			mpack_writer_init_buffer(&writer, buffer, sizeof(buffer));

			// write the example on the msgpack homepage
			mpack_start_map(&writer, 2);
			mpack_write_cstr(&writer, "compact");
			mpack_write_bool(&writer, 1);
			mpack_write_cstr(&writer, "schema");
			mpack_write_uint(&writer, 72);
			mpack_finish_map(&writer);

			// clean up
			size_t count = mpack_writer_buffer_used(&writer);
			mpack_writer_destroy(&writer);

			pic32_sendrpc(game->periph.pic32_handle, buffer, count, CYCLONE_RPC_MIWI);

			printf("Message sent !\n\n");
		}
		else if(!strncmp(command, "MyFile", 6))
		{
			printf("Loading text file !\n");
			char * msg;
			size_t len;

			pic32_sendrpc(game->periph.pic32_handle, "test.txt", 9, CYCLONE_RPC_FILE);
			while(!pic32_receive(game->periph.pic32_handle, &msg, &len, 0));

			fwrite(msg,1,len,stdout);
			free(msg);
			printf("\n");
		}
		else if(!strncmp(command, "MyMultiTouch", 12))
		{
			alt_u8 event, touchnum;
			alt_u16 x1,x2,y1,y2;

			if(mtc_get_status(game->periph.mtc_handle, &event, &touchnum, &x1, &y1, &x2, &y2))
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
			adxl345_read(game->periph.adxl345_handle, ADXL345_DATAX0, (alt_u8 *)  &c, 6);
			printf("X : %d - Y: %d, Z : %d\n", c.x, c.y, c.z);
		}
		else
			printf("Unknown Command\n");
	}
}

