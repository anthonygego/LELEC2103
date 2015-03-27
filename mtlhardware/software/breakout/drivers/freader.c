#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/alt_cache.h>

#include "freader.h"
#include "queue.h"
#include "sgdma.h"

freader_info* freader_init(alt_u32 FREADER_BASE, alt_u32 width, alt_u32 height) {
	// Initialize frame reader info
    freader_info *p = malloc(sizeof(freader_info));

    // Copy information
    p->FREADER_BASE = FREADER_BASE;
    p->current_frame = 0;
    p->displayed_frame = 0;
    p->gevent_queue = queue_new(FREADER_GEVENTS_QUEUE_SIZE);
    p->desc_queue = queue_new(FREADER_DESCS_QUEUE_SIZE);
    p->width = width;
    p->height = height;
    p->desc_sem = OSSemCreate(1);
    p->gevent_sem = OSSemCreate(1);
    p->desc_last = 0;

    freader_go(p, 0);

    // Configure frame 0
	IOWR(FREADER_BASE, FREADER_FRAME0_BASE, (alt_u32)p->frame_buffer[1]);
	IOWR(FREADER_BASE, FREADER_FRAME0_WORDS, width*height);
	IOWR(FREADER_BASE, FREADER_FRAME0_COLOR_PATTERN, width*height);
	IOWR(FREADER_BASE, FREADER_FRAME0_WIDTH, width);
	IOWR(FREADER_BASE, FREADER_FRAME0_HEIGHT, height);
	IOWR(FREADER_BASE, FREADER_FRAME0_INTERLACE, 0);

	// Configure frame 1
	IOWR(FREADER_BASE, FREADER_FRAME1_BASE, (alt_u32)p->frame_buffer[2]);
	IOWR(FREADER_BASE, FREADER_FRAME1_WORDS, width*height);
	IOWR(FREADER_BASE, FREADER_FRAME1_COLOR_PATTERN, width*height);
	IOWR(FREADER_BASE, FREADER_FRAME1_WIDTH, width);
	IOWR(FREADER_BASE, FREADER_FRAME1_HEIGHT, height);
	IOWR(FREADER_BASE, FREADER_FRAME1_INTERLACE, 0);

	IOWR(p->FREADER_BASE, 3,p->displayed_frame);

    freader_go(p, 1);

    return p;
}

void freader_uninit(freader_info* p) {
    if (p)
        free(p);
}

void freader_go(freader_info* p, alt_u8 bGo) {
    IOWR(p->FREADER_BASE, 0, bGo ? 1 : 0);
}

void freader_switch_frame(freader_info* p) {
	p->displayed_frame = !p->displayed_frame;
    IOWR(p->FREADER_BASE, 3, p->displayed_frame);
    //alt_dcache_flush_all();
}

void freader_gevent(freader_info* p, alt_u16 x, alt_u16 y, graphical_event_type type, sprite * sprite)
{
	graphical_event * ge = malloc(sizeof(graphical_event));
	ge->x = x;
	ge->y = y;
	ge->type = type;
	ge->sprite = sprite;

	alt_u8 err;

	OSSemPend(p->gevent_sem, 0, &err);
	if(!queue_push(p->gevent_queue, (alt_u32) ge))
	{
		printf("Alert ! Graphical events queue is full !!!\n");
		free(ge);
	}
	OSSemPost(p->gevent_sem);
}

void freader_desc(freader_info* p, alt_sgdma_descriptor * desc)
{
	alt_u8 err;

	OSSemPend(p->desc_sem, 0, &err);
	if(!queue_push(p->desc_queue, (alt_u32) desc))
	{
		printf("Alert ! Descriptors queue is full !!!\n");
		free(desc);
	}
	OSSemPost(p->desc_sem);
}

int freader_imgcpy_desc(freader_info *p, alt_sgdma_descriptor ** desc, alt_sgdma_descriptor * next, void * img, int x, int y, int c_width, int c_height, int t_width, int t_height) {

	*desc = (alt_sgdma_descriptor *) malloc(sizeof(alt_sgdma_descriptor)*c_height);

	void * buffer = p->frame_buffer[(!p->current_frame)+1];

	//printf("adding in buffer %d\n", (!p->current_frame)+1);

	int i;
	for(i=0; i < c_height; i++)
	{
		// One SGDMA descriptor per line
		alt_u32 * src_pos = (alt_u32 *) img + i*t_width;
		alt_u32 * dest_pos = (alt_u32 *) buffer + (y+i)*FREADER_MAX_WIDTH + x;

		alt_avalon_sgdma_construct_mem_to_mem_desc((*desc)+i, (i == c_height-1)? next: ((*desc)+i+1), src_pos, dest_pos, c_width*sizeof(alt_u32), 0, 0);
	}

	p->current_frame = !p->current_frame;
	return c_height;
}
