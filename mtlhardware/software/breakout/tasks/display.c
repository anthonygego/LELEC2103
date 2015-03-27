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
#include "freader.h"
#include "mtc.h"
#include "sgdma.h"

#include "console.h"
#include "mpack.h"
#include "breakout.h"
#include "display.h"

void display_isr(void * context)
{
	alt_u8 err;
	game_struct * game = (game_struct *) context;
	freader_info * freader = game->periph.freader_handle;
	sgdma_info * sgdma = game->periph.sgdma_handle;

	// Switch the frame
	freader_switch_frame(freader);

	OSSemPend(freader->desc_sem, 0, &err);

	free((alt_sgdma_descriptor *) (freader->desc_last));
	freader->desc_last = 0;

	if(queue_peek(freader->desc_queue))
	{
		alt_sgdma_descriptor * desc = (alt_sgdma_descriptor *) queue_pop(freader->desc_queue);
		freader->desc_last = (alt_u32) desc;
		alt_avalon_sgdma_do_async_transfer(sgdma, desc);
	}
	OSSemPost(freader->desc_sem);
}

void display_task(void* pdata)
{
	game_struct * game = (game_struct *) pdata;
	freader_info * freader = game->periph.freader_handle;

	while (1)
	{
		alt_u8 err;
		graphical_event * ge;

		OSSemPend(freader->gevent_sem, 0, &err);
		ge = (graphical_event *) queue_pop(freader->gevent_queue);
		OSSemPost(freader->gevent_sem);

		if(ge)
		{
			alt_sgdma_descriptor * desc1;
			alt_sgdma_descriptor * desc2;
			alt_sgdma_descriptor * desc3;
			alt_sgdma_descriptor * desc4;

			switch(ge->type)
			{
			case ADD:
				//printf("Add sprite in : x:%d, y : %d\n", ge->x, ge->y);

				// Making descriptor list for the image to place
				freader_imgcpy_desc(freader, &desc1, 0, ge->sprite->img_base,
						ge->x, ge->y, ge->sprite->width, ge->sprite->height, ge->sprite->width, ge->sprite->height);

				// Making descriptor list for the image to place
				freader_imgcpy_desc(freader, &desc2, 0, ge->sprite->img_base,
						ge->x, ge->y, ge->sprite->width, ge->sprite->height, ge->sprite->width, ge->sprite->height);

				freader_desc(freader, desc1);
				freader_desc(freader, desc2);

				break;
			case REMOVE:
				printf("Remove sprite in : x:%d, y : %d\n", ge->sprite->x, ge->sprite->y);
				// Making descriptor list for the image to place
				freader_imgcpy_desc(freader, &desc1, 0, ((alt_u32*)freader->frame_buffer[0] + ge->sprite->x+FREADER_MAX_WIDTH*ge->sprite->y),
						ge->sprite->x, ge->sprite->y, ge->sprite->width, ge->sprite->height, FREADER_MAX_WIDTH, FREADER_MAX_HEIGHT);

				// Making descriptor list for the image to place
				freader_imgcpy_desc(freader, &desc2, 0, ((alt_u32*)freader->frame_buffer[0] + ge->sprite->x+FREADER_MAX_WIDTH*ge->sprite->y),
						ge->sprite->x, ge->sprite->y, ge->sprite->width, ge->sprite->height, FREADER_MAX_WIDTH, FREADER_MAX_HEIGHT);

				freader_desc(freader, desc1);
				freader_desc(freader, desc2);

				break;
			case MOVE:

				// Making descriptor list for the image to place
				freader_imgcpy_desc(freader, &desc1, 0, ((alt_u32*)freader->frame_buffer[0] + ge->sprite->x+FREADER_MAX_WIDTH*ge->sprite->y),
						ge->sprite->x, ge->sprite->y, ge->sprite->width, ge->sprite->height, FREADER_MAX_WIDTH, FREADER_MAX_HEIGHT);

				// Making descriptor list for the image to place
				freader_imgcpy_desc(freader, &desc2, 0, ((alt_u32*)freader->frame_buffer[0] + ge->sprite->x+FREADER_MAX_WIDTH*ge->sprite->y),
						ge->sprite->x, ge->sprite->y, ge->sprite->width, ge->sprite->height, FREADER_MAX_WIDTH, FREADER_MAX_HEIGHT);

				// Making descriptor list for the image to place
				freader_imgcpy_desc(freader, &desc3, 0, ge->sprite->img_base,
						ge->x, ge->y, ge->sprite->width, ge->sprite->height, ge->sprite->width, ge->sprite->height);

				// Making descriptor list for the image to place
				freader_imgcpy_desc(freader, &desc4, 0, ge->sprite->img_base,
						ge->x, ge->y, ge->sprite->width, ge->sprite->height, ge->sprite->width, ge->sprite->height);

				freader_desc(freader, desc1);
				freader_desc(freader, desc2);
				freader_desc(freader, desc3);
				freader_desc(freader, desc4);

				ge->sprite->x = ge->x;
				ge->sprite->y = ge->y;

				break;
			default:
				break;
			}

			free(ge);
		}

		sgdma_info * sgdma = game->periph.sgdma_handle;

		OSSemPend(freader->desc_sem, 0, &err);
		if(queue_peek(freader->desc_queue) && !freader->desc_last)
		{
			alt_sgdma_descriptor * desc = (alt_sgdma_descriptor *) queue_pop(freader->desc_queue);
			freader->desc_last = (alt_u32) desc;
#ifdef ENABLE_ASYNC_TRANSFER
			alt_avalon_sgdma_do_async_transfer(sgdma, desc);
#else
			alt_avalon_sgdma_do_sync_transfer(sgdma, desc);
			desc = (alt_sgdma_descriptor *) queue_pop(freader->desc_queue);
			freader->desc_last = (alt_u32) desc;
			alt_avalon_sgdma_do_sync_transfer(sgdma, desc);

			if(ge && ge->type == MOVE)
			{
				desc = (alt_sgdma_descriptor *) queue_pop(freader->desc_queue);
				freader->desc_last = (alt_u32) desc;
				alt_avalon_sgdma_do_sync_transfer(sgdma, desc);
				desc = (alt_sgdma_descriptor *) queue_pop(freader->desc_queue);
				freader->desc_last = (alt_u32) desc;
				alt_avalon_sgdma_do_sync_transfer(sgdma, desc);
			}

			freader_switch_frame(freader);
			free((alt_sgdma_descriptor *) (freader->desc_last));
			freader->desc_last = 0;
#endif
		}
		OSSemPost(freader->desc_sem);

		OSTimeDlyHMSM(0, 0, 0, 10);
	}
}
