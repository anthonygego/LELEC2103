#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <system.h>
#include <includes.h>
#include <alt_types.h>
#include <sys/alt_cache.h>
#include <sys/alt_irq.h>

#include "pic32.h"
#include "display.h"
#include "mtc.h"

#include "console.h"
#include "mpack.h"
#include "breakout.h"
#include "graphics.h"

#define DISPLAY_DO_ASYNC_TRANSFER

void graphics_isr(void * context)
{
	alt_u8 err;
	game_struct * game = (game_struct *) context;
	display_info * display = game->periph.display_handle;

	// Check if frame switching is needed
	OSSemPend(display->switch_queue->sem, 0, &err);
	if(queue_peek(display->switch_queue) == display->desc_current)
	{
		queue_pop(display->switch_queue);
		display_switch_frame(display);
	}
	OSSemPost(display->switch_queue->sem);

	// Free descriptor list
	free((alt_sgdma_descriptor *) display->desc_current);
	display->desc_current = 0;

#ifdef DISPLAY_DO_ASYNC_TRANSFER
	alt_sgdma_dev * sgdma = display->sgdma;
	alt_u8 frame = !(display->displayed_frame);

	OSSemPend(display->desc_queue[frame]->sem, 0, &err);
	if(!queue_is_empty(display->desc_queue[frame]))
	{
		alt_sgdma_descriptor * desc = (alt_sgdma_descriptor *) queue_pop(display->desc_queue[frame]);
		display->desc_current = (alt_u32) desc;
		alt_avalon_sgdma_do_async_transfer(sgdma, desc);
	}
	OSSemPost(display->desc_queue[frame]->sem);
#endif

}

void graphics_task(void* pdata)
{
	game_struct * game = (game_struct *) pdata;
	display_info * display = game->periph.display_handle;
	alt_sgdma_dev * sgdma = display->sgdma;

	while (1)
	{
		if(!(display->desc_current))
		{
			alt_u8 err;

			// Send a descriptor list to SGDMA if queue is not empty

			alt_u8 frame = !(display->displayed_frame);
			OSSemPend(display->desc_queue[frame]->sem, 0, &err);
			if(!queue_is_empty(display->desc_queue[frame]))
			{
				alt_sgdma_descriptor * desc = (alt_sgdma_descriptor *) queue_pop(display->desc_queue[frame]);
				display->desc_current = (alt_u32) desc;
#ifdef DISPLAY_DO_ASYNC_TRANSFER
				alt_avalon_sgdma_do_async_transfer(sgdma, desc);
#else
				alt_avalon_sgdma_do_sync_transfer(sgdma, desc);
				graphics_isr(game);
#endif
			}
			OSSemPost(display->desc_queue[frame]->sem);
		}

		OSTimeDlyHMSM(0, 0, 0, 5);
	}
}
