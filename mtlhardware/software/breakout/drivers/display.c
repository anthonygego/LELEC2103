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

display_info* display_init(alt_u32 mixer_base, alt_u32 bg_frame_base, alt_u32 sprite0_base, alt_u32 sprite1_base, const char * sgdma_name, alt_avalon_sgdma_callback sgdma_callback, void *sgdma_context) {
	// Initialize frame reader info
    display_info *p = malloc(sizeof(display_info));

    // Copy information
    p->bg_frame_base = bg_frame_base;
    p->sprite_base[0] = sprite0_base;
    p->sprite_base[1] = sprite1_base;
    p->mixer_base = mixer_base;
    p->displayed_frame = 0;
    p->desc_queue[0] = queue_new(DISPLAY_DESCS_QUEUE_SIZE);
    p->desc_queue[1] = queue_new(DISPLAY_DESCS_QUEUE_SIZE);
    p->switch_queue = queue_new(DISPLAY_DESCS_QUEUE_SIZE);
    p->desc_current = 0;
    p->alt_frame = 1;

    // Activate mixer display
	IOWR(p->mixer_base, 0, 1);
	IOWR(p->mixer_base, MIXER_LAYER0_ACTIVE, 0);
	IOWR(p->mixer_base, MIXER_LAYER0_ACTIVE+3, 0);

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


    IOWR(ALPHA_BALL_BASE, 0, 0);
	IOWR(ALPHA_BALL_BASE, DISPLAY_FRAME0_BASE, (alt_u8) TEXTURES_BASE + 400*4);
	IOWR(ALPHA_BALL_BASE, DISPLAY_FRAME0_WORDS, 100);
	IOWR(ALPHA_BALL_BASE, DISPLAY_FRAME0_COLOR_PATTERN, 400);
	IOWR(ALPHA_BALL_BASE, DISPLAY_FRAME0_WIDTH, 20);
	IOWR(ALPHA_BALL_BASE, DISPLAY_FRAME0_HEIGHT, 20);
	IOWR(ALPHA_BALL_BASE, DISPLAY_FRAME0_INTERLACE, 1);
	IOWR(ALPHA_BALL_BASE, 0, 1);

	IOWR(ALPHA_PADDLE_BASE, 0, 0);
	IOWR(ALPHA_PADDLE_BASE, DISPLAY_FRAME0_BASE, (alt_u8) TEXTURES_BASE + 4500*4);
	IOWR(ALPHA_PADDLE_BASE, DISPLAY_FRAME0_WORDS, 1000);
	IOWR(ALPHA_PADDLE_BASE, DISPLAY_FRAME0_COLOR_PATTERN, 4000);
	IOWR(ALPHA_PADDLE_BASE, DISPLAY_FRAME0_WIDTH, 200);
	IOWR(ALPHA_PADDLE_BASE, DISPLAY_FRAME0_HEIGHT, 20);
	IOWR(ALPHA_PADDLE_BASE, DISPLAY_FRAME0_INTERLACE, 1);
	IOWR(ALPHA_PADDLE_BASE, 0, 1);

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

void display_push_desc(display_info* p, alt_sgdma_descriptor * desc, alt_u8 frame)
{
	alt_u8 err;

	OSSemPend(p->desc_queue[frame]->sem, 0, &err);

	if(!queue_push(p->desc_queue[frame], (alt_u32) desc))
		free(desc);

	OSSemPost(p->desc_queue[frame]->sem);
}

void display_add_sprite(display_info *p, sprite *s)
{
	if(!s->type)
	{
		alt_sgdma_descriptor * desc1;
		alt_sgdma_descriptor * desc2;

		// Making descriptor list for the image to place
		desc1 = display_imgcpy_desc(p, 0, s, s->img_base, s->width, s->height);

		// Making descriptor list for the image to place
		desc2 = display_imgcpy_desc(p, 1, s, s->img_base, s->width, s->height);

		display_push_desc(p, desc1, 0);
		display_push_desc(p, desc2, 1);
	}
	else
	{
		IOWR(p->sprite_base[s->type-1], 0, 0);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_BASE, (alt_u32) s->img_base);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_WORDS, s->width*s->height);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_COLOR_PATTERN, s->width*s->height);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_WIDTH, s->width);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_HEIGHT, s->height);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_INTERLACE, 1);
		IOWR(p->sprite_base[s->type-1], 0, 1);
		IOWR(p->mixer_base, MIXER_LAYER0_X+(s->type-1)*3, s->x);
		IOWR(p->mixer_base, MIXER_LAYER0_Y+(s->type-1)*3, s->y);
		IOWR(p->mixer_base, MIXER_LAYER0_ACTIVE+(s->type-1)*3, 1);
	}

}

void display_remove_sprite(display_info *p, sprite *s)
{
	if(!s->type)
	{
		alt_sgdma_descriptor * desc1;
		alt_sgdma_descriptor * desc2;

		// Making descriptor list for the image to place
		desc1 = display_imgcpy_desc(p, 0, s, ((alt_u32*)p->frame_buffer[0] + s->x+DISPLAY_MAX_WIDTH*s->y), DISPLAY_MAX_WIDTH, DISPLAY_MAX_HEIGHT);

		// Making descriptor list for the image to place
		desc2 = display_imgcpy_desc(p, 1, s, ((alt_u32*)p->frame_buffer[0] + s->x+DISPLAY_MAX_WIDTH*s->y), DISPLAY_MAX_WIDTH, DISPLAY_MAX_HEIGHT);

		display_push_desc(p, desc1, 0);
		display_push_desc(p, desc2, 1);
	}
	else
	{
		IOWR(p->sprite_base[s->type-1], 0, 0);
		IOWR(p->mixer_base, MIXER_LAYER0_ACTIVE+(s->type-1)*3, 0);
	}
}

void display_move_sprite(display_info *p, sprite *s, int to_x, int to_y)
{
	if(!s->type)
	{
		display_remove_sprite(p, s);
		s->x = to_x;
		s->y = to_y;
		display_add_sprite(p,s);
	}
	else
	{
		s->x = to_x;
		s->y = to_y;
		IOWR(p->mixer_base, MIXER_LAYER0_X+(s->type-1)*3, s->x);
		IOWR(p->mixer_base, MIXER_LAYER0_Y+(s->type-1)*3, s->y);
	}
}

void display_end_frame(display_info *p)
{
	alt_u8 err;
	OSSemPend(p->switch_queue->sem, 0, &err);

	if(queue_last(p->switch_queue) != queue_last(p->desc_queue[p->alt_frame]))
	{
		queue_push(p->switch_queue, queue_last(p->desc_queue[p->alt_frame]));
		p->alt_frame = !(p->alt_frame);
	}

	OSSemPost(p->switch_queue->sem);


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
