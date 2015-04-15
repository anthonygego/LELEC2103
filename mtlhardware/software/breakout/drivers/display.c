#include <io.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/alt_cache.h>
#include <altera_avalon_sgdma.h>
#include <altera_avalon_sgdma_regs.h>
#include <altera_avalon_sgdma_descriptor.h>

#include "display.h"
#include "queue.h"

display_info* display_init(alt_u32 mixer_base, alt_u32 bg_frame_base, const char * sgdma_name, alt_avalon_sgdma_callback sgdma_callback, void *sgdma_context) {
	// Initialize frame reader info
    display_info *p = malloc(sizeof(display_info));

    // Activate mixer display
    IOWR(mixer_base, 0, 1);

    // Copy information
    p->bg_frame_base = bg_frame_base;
    p->displayed_frame = 0;
    p->desc_queue[0] = queue_new(DISPLAY_DESCS_QUEUE_SIZE);
    p->desc_queue[1] = queue_new(DISPLAY_DESCS_QUEUE_SIZE);
    p->switch_queue = queue_new(DISPLAY_DESCS_QUEUE_SIZE);
    p->desc_current = 0;
    p->alt_frame = 1;

    // Init SGDMA
    p->sgdma = alt_avalon_sgdma_open(sgdma_name);
	alt_avalon_sgdma_register_callback(p->sgdma, sgdma_callback,
			(ALTERA_AVALON_SGDMA_CONTROL_IE_GLOBAL_MSK | ALTERA_AVALON_SGDMA_CONTROL_IE_CHAIN_COMPLETED_MSK ), sgdma_context);

    display_go(p, 0);

    // Configure frame 0
	IOWR(bg_frame_base, DISPLAY_FRAME0_BASE, (alt_u32)p->frame_buffer[1]);
	IOWR(bg_frame_base, DISPLAY_FRAME0_WORDS, DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT);
	IOWR(bg_frame_base, DISPLAY_FRAME0_COLOR_PATTERN, DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT);
	IOWR(bg_frame_base, DISPLAY_FRAME0_WIDTH, DISPLAY_MAX_WIDTH);
	IOWR(bg_frame_base, DISPLAY_FRAME0_HEIGHT, DISPLAY_MAX_HEIGHT);
	IOWR(bg_frame_base, DISPLAY_FRAME0_INTERLACE, 1);

	// Configure frame 1
	IOWR(bg_frame_base, DISPLAY_FRAME1_BASE, (alt_u32)p->frame_buffer[2]);
	IOWR(bg_frame_base, DISPLAY_FRAME1_WORDS, DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT);
	IOWR(bg_frame_base, DISPLAY_FRAME1_COLOR_PATTERN, DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT);
	IOWR(bg_frame_base, DISPLAY_FRAME1_WIDTH, DISPLAY_MAX_WIDTH);
	IOWR(bg_frame_base, DISPLAY_FRAME1_HEIGHT, DISPLAY_MAX_HEIGHT);
	IOWR(bg_frame_base, DISPLAY_FRAME1_INTERLACE, 1);

	IOWR(p->bg_frame_base, 3,p->displayed_frame);

    display_go(p, 1);

    return p;
}

void display_uninit(display_info* p) {
    if (p)
    {
    	if(p->sgdma)
    		free(p->sgdma);
        free(p);
    }
}

void display_go(display_info* p, alt_u8 bGo) {
    IOWR(p->bg_frame_base, 0, bGo ? 1 : 0);
}

void display_switch_frame(display_info* p) {
	p->displayed_frame = !p->displayed_frame;
    IOWR(p->bg_frame_base, 3, p->displayed_frame);
}

void display_push_desc(display_info* p, alt_sgdma_descriptor * desc, alt_u8 frame, alt_u8 end_frame)
{
	alt_u8 err;

	OSSemPend(p->desc_queue[frame]->sem, 0, &err);
	err = !queue_push(p->desc_queue[frame], (alt_u32) desc);

	if(err)
	{
		//printf("Alert ! Descriptors queue is full !!!\n");
		free(desc);
	}
	else if(end_frame && frame == p->alt_frame)
	{
		OSSemPend(p->switch_queue->sem, 0, &err);
		queue_push(p->switch_queue, (alt_u32) desc);
		OSSemPost(p->switch_queue->sem);
	}

	OSSemPost(p->desc_queue[frame]->sem);
}

void display_add_sprite(display_info *p, sprite *s, alt_u8 end_frame)
{
	if(1)
	{
		alt_sgdma_descriptor * desc1;
		alt_sgdma_descriptor * desc2;

		// Making descriptor list for the image to place
		desc1 = display_imgcpy_desc(p, 0, s, s->img_base, s->width, s->height);

		// Making descriptor list for the image to place
		desc2 = display_imgcpy_desc(p, 1, s, s->img_base, s->width, s->height);

		display_push_desc(p, desc1, 0, end_frame);
		display_push_desc(p, desc2, 1, end_frame);
		if(end_frame)
			p->alt_frame = !(p->alt_frame);
	}

}

void display_remove_sprite(display_info *p, sprite *s, alt_u8 end_frame)
{
	if(1)
	{
		alt_sgdma_descriptor * desc1;
		alt_sgdma_descriptor * desc2;

		// Making descriptor list for the image to place
		desc1 = display_imgcpy_desc(p, 0, s, ((alt_u32*)p->frame_buffer[0] + s->x+DISPLAY_MAX_WIDTH*s->y), DISPLAY_MAX_WIDTH, DISPLAY_MAX_HEIGHT);

		// Making descriptor list for the image to place
		desc2 = display_imgcpy_desc(p, 1, s, ((alt_u32*)p->frame_buffer[0] + s->x+DISPLAY_MAX_WIDTH*s->y), DISPLAY_MAX_WIDTH, DISPLAY_MAX_HEIGHT);

		display_push_desc(p, desc1, 0, end_frame);
		display_push_desc(p, desc2, 1, end_frame);
		if(end_frame)
				p->alt_frame = !(p->alt_frame);
	}
}

void display_move_sprite(display_info *p, sprite *s, alt_u8 end_frame, int to_x, int to_y)
{
	if(1)
	{
		display_remove_sprite(p, s, 0);
		s->x = to_x;
		s->y = to_y;
		display_add_sprite(p,s, end_frame);
	}
}

alt_sgdma_descriptor * display_imgcpy_desc(display_info *p, alt_u8 frame, sprite * s, void * img, int t_width, int t_height) {

	alt_sgdma_descriptor * desc = (alt_sgdma_descriptor *) malloc(sizeof(alt_sgdma_descriptor)*s->height);
	void * buffer = p->frame_buffer[frame+1];

	int i;
	for(i=0; i < s->height; i++)
	{
		// One SGDMA descriptor per line
		alt_u32 * src_pos = (alt_u32 *) img + i*t_width;
		alt_u32 * dest_pos = (alt_u32 *) buffer + (s->y+i)*DISPLAY_MAX_WIDTH + s->x;
		alt_u32 c_size =  s->width*sizeof(alt_u32);

		alt_avalon_sgdma_construct_mem_to_mem_desc(desc+i, (i == s->height-1)? 0: (desc+i+1), src_pos, dest_pos, c_size, 0, 0);
	}

	return desc;
}
