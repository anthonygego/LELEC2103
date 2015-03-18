#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <includes.h>
#include <alt_types.h>

#include "pic32.h"
#include "mpack.h"
#include "rpc.h"

void rpc_task(void* pdata)
{
	while (1)
	{
		char * msg;
		size_t len;

		if(pic32_receive(&msg, &len, 1))
		{
			printf("\n---\nReceived RPC message of size %d ! \n", len);
			// parse a data buffer into a node tree
			mpack_tree_t tree;
			mpack_tree_init(&tree, msg, len);
			mpack_node_t* root = mpack_tree_root(&tree);

			// extract the example data on the msgpack homepage
			alt_u8 compact = mpack_node_bool(mpack_node_map_cstr(root, "compact"));
			int schema = mpack_node_i32(mpack_node_map_cstr(root, "schema"));

			// clean up and check for errors
			mpack_tree_destroy(&tree);

			printf("Read values : %d - %d\n", compact, schema);
			free(msg);
			printf("---\n");
		}
		OSTimeDlyHMSM(0, 0, 0, 20);
	}
}
