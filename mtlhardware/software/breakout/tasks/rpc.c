#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <includes.h>
#include <alt_types.h>

#include "pic32.h"
#include "mtc.h"
#include "rpc.h"
#include "mpack.h"
#include "breakout.h"

void rpc_game_event(game_struct * game, game_event ge)
{
	alt_u8 err;
	OSSemPend(game->events_queue->sem, 0, &err);
	queue_push(game->events_queue, ge);
	OSSemPost(game->events_queue->sem);
}

void rpc_task(void* pdata)
{
	game_struct * game = (game_struct *) pdata;

	while (1)
	{
		char * msg;
		size_t len;

		if(pic32_receive(game->periph.pic32_handle, &msg, &len, 1))
		{
			printf("---Received RPC message of size %d !\n", len);
			// parse a data buffer into a node tree
			mpack_tree_t tree;
			mpack_tree_init(&tree, msg, len);
			mpack_node_t* root = mpack_tree_root(&tree);

			// extract the example data on the msgpack homepage
			alt_u8 msgtype = mpack_node_bool(mpack_node_map_cstr(root, "msgtype"));

			switch(msgtype)
			{
			case 0:
				// Game event
				rpc_game_event(game, mpack_node_i32(mpack_node_map_cstr(root, "value")));
				break;
			default:
				break;
			}

			// clean up and check for errors
			mpack_tree_destroy(&tree);

			free(msg);
		}
		OSTimeDlyHMSM(0, 0, 0, 200);
	}
}

