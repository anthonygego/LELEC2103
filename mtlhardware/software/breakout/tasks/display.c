#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <includes.h>
#include <alt_types.h>

#include "pic32.h"
#include "freader.h"
#include "mtc.h"
#include "console.h"
#include "mpack.h"
#include "breakout.h"

void display_task(void* pdata)
{
	game_state * game = (game_state *) pdata;
	int i,j;

	printf("-- Making some gradients\n");

	for(j=0; j<800; j++)
		for(i=0; i<480; i++)
			game->freader_handle->frame_buffer[0].tab[i][j] = 0xff0000 + ((i*255/480) << 8);

	printf("-- Gradient 1 done\n");

	for(j=0; j<800; j++)
			for(i=0; i<480; i++)
				game->freader_handle->frame_buffer[1].tab[i][j] = 0xff00ff - (i*255/480/2);

	printf("-- Gradient 2 done\n");

	while (1)
	{
		freader_select_frame(game->freader_handle, !game->freader_handle->current_frame);
		OSTimeDlyHMSM(0, 0, 0, 500);
	}
}
