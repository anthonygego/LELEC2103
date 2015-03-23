#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <includes.h>
#include <alt_types.h>

#include "pic32.h"
#include "mtc.h"
#include "console.h"
#include "mpack.h"
#include "breakout.h"

void console_task(void* pdata)
{
	game_state * game = (game_state *) pdata;

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
		else if(!strncmp(command, "MyMIWI", 6))
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

			pic32_sendrpc(game->pic32_handle, buffer, count, CYCLONE_RPC_MIWI);

			printf("Message sent !\n\n");
		}
		else if(!strncmp(command, "MyFile", 6))
		{
			printf("Loading text file !\n");
			char * msg;
			size_t len;

			pic32_sendrpc(game->pic32_handle, "test.txt", 9, CYCLONE_RPC_FILE);
			while(!pic32_receive(game->pic32_handle, &msg, &len, 0));

			fwrite(msg,1,len,stdout);
			printf("\n");
		}
		else if(!strncmp(command, "MyMultiTouch", 12))
		{
			alt_u8 event, touchnum;
			int x1,x2,y1,y2;

			if(mtc_get_status(game->mtc_handle, &event, &touchnum, &x1, &y1, &x2, &y2))
				if(touchnum == 2)
					printf("x1: %3d, y1: %3d\nx2: %3d, y2: %3d\nTouch num : %d\nEvent : 0x%X\n", x1, y1, x2, y2, touchnum, event);
				else
					printf("x1: %3d, y1: %3d\nTouch num : %d\nEvent : 0x%X\n", x1, y1, touchnum, event);
			else
				printf("No new point\n");
		}
		else
			printf("Unknown Command\n");
	}
}

