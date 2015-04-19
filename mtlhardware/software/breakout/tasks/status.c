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
#include "tasks.h"
#include "mpack.h"
#include "breakout.h"

void status_task(void* pdata)
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
		mpack_write_i32(&writer, game->paddle.width);

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

		alt_u8 err;
		OSSemPend(game->pic32_handle->sem, 0, &err);
		pic32_sendrpc(game->pic32_handle, buffer, count, CYCLONE_RPC_INFO);
		OSSemPost(game->pic32_handle->sem);

		OSTimeDlyHMSM(0, 0, 1, 0);
	}
}
