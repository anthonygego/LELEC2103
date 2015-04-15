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

display_info* display_init(alt_u32 DISPLAY_BASE, const char * sgdma_name, alt_avalon_sgdma_callback sgdma_callback, void *sgdma_context) {
	// Initialize frame reader info
    display_info *p = malloc(sizeof(display_info));

    // Copy information
    p->DISPLAY_BASE = DISPLAY_BASE;
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
	IOWR(DISPLAY_BASE, DISPLAY_FRAME0_BASE, (alt_u32)p->frame_buffer[1]);
	IOWR(DISPLAY_BASE, DISPLAY_FRAME0_WORDS, DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT);
	IOWR(DISPLAY_BASE, DISPLAY_FRAME0_COLOR_PATTERN, DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT);
	IOWR(DISPLAY_BASE, DISPLAY_FRAME0_WIDTH, DISPLAY_MAX_WIDTH);
	IOWR(DISPLAY_BASE, DISPLAY_FRAME0_HEIGHT, DISPLAY_MAX_HEIGHT);
	IOWR(DISPLAY_BASE, DISPLAY_FRAME0_INTERLACE, 1);

	// Configure frame 1
	IOWR(DISPLAY_BASE, DISPLAY_FRAME1_BASE, (alt_u32)p->frame_buffer[2]);
	IOWR(DISPLAY_BASE, DISPLAY_FRAME1_WORDS, DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT);
	IOWR(DISPLAY_BASE, DISPLAY_FRAME1_COLOR_PATTERN, DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT);
	IOWR(DISPLAY_BASE, DISPLAY_FRAME1_WIDTH, DISPLAY_MAX_WIDTH);
	IOWR(DISPLAY_BASE, DISPLAY_FRAME1_HEIGHT, DISPLAY_MAX_HEIGHT);
	IOWR(DISPLAY_BASE, DISPLAY_FRAME1_INTERLACE, 1);

	IOWR(p->DISPLAY_BASE, 3,p->displayed_frame);

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
    IOWR(p->DISPLAY_BASE, 0, bGo ? 1 : 0);
}

void display_switch_frame(display_info* p) {
	p->displayed_frame = !p->displayed_frame;
    IOWR(p->DISPLAY_BASE, 3, p->displayed_frame);
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
	alt_sgdma_descriptor * desc1;
	alt_sgdma_descriptor * desc2;

	// Making descriptor list for the image to place
	if(s->texture)
		desc1 = display_texcpy_desc(p, 0, s, s->img_base, s->texture);
	else
		desc1 = display_imgcpy_desc(p, 0, s, s->img_base, s->width, s->height);

	// Making descriptor list for the image to place
	if(s->texture)
		desc2 = display_texcpy_desc(p, 1, s, s->img_base, s->texture);
	else
		desc2 = display_imgcpy_desc(p, 1, s, s->img_base, s->width, s->height);

	display_push_desc(p, desc1, 0, end_frame);
	display_push_desc(p, desc2, 1, end_frame);
	if(end_frame)
		p->alt_frame = !(p->alt_frame);

}

void display_remove_sprite(display_info *p, sprite *s, alt_u8 end_frame)
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

void display_move_sprite(display_info *p, sprite *s, alt_u8 end_frame, int to_x, int to_y)
{
	display_remove_sprite(p, s, 0);
	s->x = to_x;
	s->y = to_y;
	display_add_sprite(p,s, end_frame);
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

		if(s->alpha)
		{
			alt_u8 j = 0;
			while(*(s->img_base+i*s->width+j) == s->alpha && j< (s->width/2)-1) j++;
			src_pos += j;
			dest_pos += j;
			c_size = (s->width-2*j)*sizeof(alt_u32);
		}

		alt_avalon_sgdma_construct_mem_to_mem_desc(desc+i, (i == s->height-1)? 0: (desc+i+1), src_pos, dest_pos, c_size, 0, 0);
	}

	return desc;
}

alt_sgdma_descriptor * display_texcpy_desc(display_info *p, alt_u8 frame, sprite * s, void * tex, int t_size)
{
	int c_pixels = s->width/t_size;
	int r_pixels = s->width%t_size;

	alt_sgdma_descriptor * desc = (alt_sgdma_descriptor *) malloc(sizeof(alt_sgdma_descriptor)*(c_pixels+(r_pixels != 0))*s->height);
	void * buffer = p->frame_buffer[frame+1];

	alt_u32 * src_pos = (alt_u32 *) tex;

	int i, j;
	int cc_size = 0;
	for(i=0; i < s->height; i++)
	{
		int jcnt = c_pixels+(r_pixels != 0);
		for(j=0; j < jcnt; j++)
		{
			alt_u32 * dest_pos = (alt_u32 *) buffer + (s->y+i)*DISPLAY_MAX_WIDTH + s->x + j*(t_size);
			alt_u32 c_size =  (j== jcnt-1) && (r_pixels != 0) ? r_pixels*sizeof(alt_u32) : t_size*sizeof(alt_u32);

			alt_avalon_sgdma_construct_mem_to_mem_desc(desc+i*jcnt+j, (i == s->height-1) && (j==jcnt-1)? 0: (desc+i*jcnt+j+1), src_pos, dest_pos, c_size, 0, 0);
			cc_size += c_size;
			src_pos = (alt_u32*)tex + (cc_size/sizeof(alt_u32))%t_size;
		}
	}

	return desc;
}
