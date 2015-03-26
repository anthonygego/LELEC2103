#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <system.h>
#include <includes.h>
#include <alt_types.h>
#include <sys/alt_cache.h>

#include "pic32.h"
#include "freader.h"
#include "mtc.h"
#include "sgdma.h"

#include "console.h"
#include "mpack.h"
#include "breakout.h"

void display_task(void* pdata)
{
	game_state * game = (game_state *) pdata;
	int i,j;

	printf("-- Making gradients\n");

	for(i=0; i<480; i++)
		for(j=0; j<800; j++)
			game->freader_handle->frame_buffer[0][i][j] = 0xff0000 + ((i*255/480) << 8);

	for(i=0; i<480; i++)
		for(j=0; j<800; j++)
			game->freader_handle->frame_buffer[1][i][j] = 0xff00ff + ((i*255/240) << 8);

	int testimg[4000];
		for(i=0; i<4000; i++)
			testimg[i] = i<2000 ? 0xffff00 : 0xffffff;

		alt_dcache_flush_all(); // Héhé... :-(

	printf("-- SGDMA Copy\n");
	sgdma_memcpy(game->sgdma_handle, game->freader_handle->frame_buffer[1], game->freader_handle->frame_buffer[0], 800*240*sizeof(int));

	sgdma_imgcpy(game->sgdma_handle, testimg, game->freader_handle->frame_buffer[0], 50, 100, 40, 20, 200, 20);
	sgdma_imgcpy(game->sgdma_handle, testimg, game->freader_handle->frame_buffer[0], 500, 100, 100, 20, 200, 20);
	sgdma_imgcpy(game->sgdma_handle, testimg, game->freader_handle->frame_buffer[0], 50, 20, 200, 20, 200, 20);
	while (1)
	{
		OSTimeDlyHMSM(0, 0, 0, 200);
		freader_select_frame(game->freader_handle, !game->freader_handle->current_frame);
	}
}
