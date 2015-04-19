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
#include "simpletext.h"

alt_sgdma_descriptor * display_imgcpy_desc(display_info *p, alt_u8 frame, sprite s, void * img, int t_width, int t_height);
alt_sgdma_descriptor * display_memcpy_desc(alt_u32 * src, alt_u32 * dest, alt_u32 length);

display_info* display_init(alt_u32 mixer_base, alt_u32 bg_frame_base, alt_u32 sprite0_base, alt_u32 sprite1_base, alt_u32 alpha0_base, alt_u32 alpha1_base, const char * sgdma_name) {
	// Initialize frame reader info
    display_info *p = malloc(sizeof(display_info));

    // Copy information
    p->bg_frame_base = bg_frame_base;
    p->sprite_base[0] = sprite0_base;
    p->sprite_base[1] = sprite1_base;
    p->alpha_base[0] = alpha0_base;
    p->alpha_base[1] = alpha1_base;
    p->mixer_base = mixer_base;
    p->displayed_frame = 0;
    p->desc_queue[0] = queue_new(DISPLAY_DESCS_QUEUE_SIZE);
    p->desc_queue[1] = queue_new(DISPLAY_DESCS_QUEUE_SIZE);
    p->text_queue[0] = queue_new(DISPLAY_DESCS_QUEUE_SIZE);
    p->text_queue[1] = queue_new(DISPLAY_DESCS_QUEUE_SIZE);

    // Initialize mixer
	IOWR(p->mixer_base, 0, 1);
	IOWR(p->mixer_base, MIXER_LAYER0_ACTIVE, 0);
	IOWR(p->mixer_base, MIXER_LAYER0_ACTIVE+3, 0);

    // Initialize SGDMA
    p->sgdma = alt_avalon_sgdma_open(sgdma_name);

    IOWR(p->bg_frame_base, 0, 0);

    // Configure frame 0
	IOWR(p->bg_frame_base, DISPLAY_FRAME0_BASE, (alt_u32)p->frame_buffer[1]);
	IOWR(p->bg_frame_base, DISPLAY_FRAME0_WORDS, DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT);
	IOWR(p->bg_frame_base, DISPLAY_FRAME0_COLOR_PATTERN, DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT);
	IOWR(p->bg_frame_base, DISPLAY_FRAME0_WIDTH, DISPLAY_MAX_WIDTH);
	IOWR(p->bg_frame_base, DISPLAY_FRAME0_HEIGHT, DISPLAY_MAX_HEIGHT);
	IOWR(p->bg_frame_base, DISPLAY_FRAME0_INTERLACE, 1);

	// Configure frame 1
	IOWR(p->bg_frame_base, DISPLAY_FRAME1_BASE, (alt_u32)p->frame_buffer[2]);
	IOWR(p->bg_frame_base, DISPLAY_FRAME1_WORDS, DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT);
	IOWR(p->bg_frame_base, DISPLAY_FRAME1_COLOR_PATTERN, DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT);
	IOWR(p->bg_frame_base, DISPLAY_FRAME1_WIDTH, DISPLAY_MAX_WIDTH);
	IOWR(p->bg_frame_base, DISPLAY_FRAME1_HEIGHT, DISPLAY_MAX_HEIGHT);
	IOWR(p->bg_frame_base, DISPLAY_FRAME1_INTERLACE, 1);

	IOWR(p->bg_frame_base, 3, p->displayed_frame);

	IOWR(p->bg_frame_base, 0, 1);

    return p;
}

void display_uninit(display_info* p) {
    if (p) {
    	if(p->sgdma) {
    		free(p->sgdma);
    		queue_delete(p->desc_queue[0]);
    		queue_delete(p->desc_queue[1]);
    	}
        free(p);
    }
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

void display_push_dt(display_info* p, display_text * dt, alt_u8 frame)
{
	alt_u8 err;
	OSSemPend(p->text_queue[frame]->sem, 0, &err);
	if(!queue_push(p->text_queue[frame], (alt_u32) dt))
		free(dt);
	OSSemPost(p->text_queue[frame]->sem);
}

void display_add_text(display_info *p, alt_u16 x, alt_u16 y, alt_u32 color, font_struct * font, char* text)
{
	alt_u8 i;
	for(i=0; i<2; i++) {
		display_text * dt = malloc(sizeof(display_text));
		dt->x = x;
		dt->y = y;
		dt->text = text;
		dt->color = color;
		dt->font = font;

		// Push to the queue
		display_push_dt(p, dt, i);
	}

}

void display_add_sprite(display_info *p, sprite s)
{
	if(s.x < 0 || s.x > DISPLAY_MAX_WIDTH-s.width || s.y < 0 || s.y > DISPLAY_MAX_HEIGHT-s.height) {
		printf("Assert error adding sprite to : %d, %d!\n", s.x, s.y);
		return;
	}

	if(!s.type) {
		// Same copies for the 2 frames
		alt_sgdma_descriptor * desc1 = display_imgcpy_desc(p, 0, s, s.img_base, s.width, s.height);
		alt_sgdma_descriptor * desc2 = display_imgcpy_desc(p, 1, s, s.img_base, s.width, s.height);

		// Push to the queue
		display_push_desc(p, desc1, 0);
		display_push_desc(p, desc2, 1);
	}
	else {
		IOWR(p->mixer_base, MIXER_LAYER0_X+(s.type-1)*3, s.x);
		IOWR(p->mixer_base, MIXER_LAYER0_Y+(s.type-1)*3, s.y);
		IOWR(p->mixer_base, MIXER_LAYER0_ACTIVE+(s.type-1)*3, 1);
	}

}

void display_remove_sprite(display_info *p, sprite s) {
	if(s.x < 0 || s.x > DISPLAY_MAX_WIDTH-s.width || s.y < 0 || s.y > DISPLAY_MAX_HEIGHT-s.height) {
		printf("Assert error removing sprite to : %d, %d!\n", s.x, s.y);
		return;
	}

	if(!s.type) {
		// Same copies for the 2 frames
		alt_sgdma_descriptor * desc1 = display_imgcpy_desc(p, 0, s, ((alt_u32*)p->frame_buffer[0] + s.x+DISPLAY_MAX_WIDTH*s.y), DISPLAY_MAX_WIDTH, DISPLAY_MAX_HEIGHT);
		alt_sgdma_descriptor * desc2 = display_imgcpy_desc(p, 1, s, ((alt_u32*)p->frame_buffer[0] + s.x+DISPLAY_MAX_WIDTH*s.y), DISPLAY_MAX_WIDTH, DISPLAY_MAX_HEIGHT);

		// Push to the queue
		display_push_desc(p, desc1, 0);
		display_push_desc(p, desc2, 1);
	}
	else // else we deactivate hardware sprite
		IOWR(p->mixer_base, MIXER_LAYER0_ACTIVE+(s.type-1)*3, 0);
}

void display_move_sprite(display_info *p, sprite *s, int to_x, int to_y) {
	if(to_x < 0 || to_x > DISPLAY_MAX_WIDTH-s->width || to_y < 0 || to_y > DISPLAY_MAX_HEIGHT-s->height) {
		printf("Assert error moving sprite to : %d, %d!\n", to_x, to_y);
		return;
	}

	if(!s->type) { // If software sprite, remove and add
		display_remove_sprite(p, *s);
		s->x = to_x;
		s->y = to_y;
		display_add_sprite(p, *s);
	}
	else { // else move by changing registers values
		s->x = to_x;
		s->y = to_y;
		IOWR(p->mixer_base, MIXER_LAYER0_X+(s->type-1)*3, s->x);
		IOWR(p->mixer_base, MIXER_LAYER0_Y+(s->type-1)*3, s->y);
	}
}

void display_end_frame(display_info *p)
{
	alt_u8 err, i;

	for(i=0; i<2; i++)
	{
		OSSemPend(p->desc_queue[!p->displayed_frame]->sem, 0, &err);
		while(!queue_is_empty(p->desc_queue[!p->displayed_frame])) {
			alt_sgdma_descriptor * desc = (alt_sgdma_descriptor *) queue_pop(p->desc_queue[!p->displayed_frame]);
			alt_avalon_sgdma_do_sync_transfer(p->sgdma, desc);
			free(desc);
		}
		OSSemPost(p->desc_queue[!p->displayed_frame]->sem);

		OSSemPend(p->text_queue[!p->displayed_frame]->sem, 0, &err);
		while(!queue_is_empty(p->text_queue[!p->displayed_frame])) {
			display_text * dt = (display_text *) queue_pop(p->text_queue[!p->displayed_frame]);
			simpletext_print(p, dt->x, dt->y, dt->color, dt->font, dt->text);
			free(dt);
		}
		OSSemPost(p->text_queue[!p->displayed_frame]->sem);

		if(i==0)
			display_switch_frame(p);
	}
}

void display_clear_screen(display_info *p)
{
	alt_sgdma_descriptor * desc1 = display_memcpy_desc((alt_u32*) p->frame_buffer[1], (alt_u32*) p->frame_buffer[3], DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT*4);
	alt_sgdma_descriptor * desc2 = display_memcpy_desc((alt_u32*) p->frame_buffer[2], (alt_u32*) p->frame_buffer[3], DISPLAY_MAX_WIDTH*DISPLAY_MAX_HEIGHT*4);

	// Push to the queue
	display_push_desc(p, desc1, 0);
	display_push_desc(p, desc2, 1);
}

alt_sgdma_descriptor * display_memcpy_desc(alt_u32 * dest, alt_u32 * src, alt_u32 length) {

	alt_u32 nbr_desc = (length+SGDMA_MAX_BLOCK_SIZE-1)/SGDMA_MAX_BLOCK_SIZE;
	alt_sgdma_descriptor * desc = (alt_sgdma_descriptor *) malloc(sizeof(alt_sgdma_descriptor)*nbr_desc);

	int i;
	for(i=0; i<nbr_desc; i++) {
		// One SGDMA descriptor per line
		alt_u32 * src_pos = (alt_u32 *) src + i*SGDMA_MAX_BLOCK_SIZE/4;
		alt_u32 * dest_pos = (alt_u32 *) dest + i*SGDMA_MAX_BLOCK_SIZE/4;
		alt_u32 c_size = (i==nbr_desc-1) ? length - i*SGDMA_MAX_BLOCK_SIZE : SGDMA_MAX_BLOCK_SIZE;

		alt_avalon_sgdma_construct_mem_to_mem_desc(desc+i, (i==nbr_desc-1)? 0: (desc+i+1), src_pos, dest_pos, c_size, 0, 0);
	}

	return desc;
}

alt_sgdma_descriptor * display_imgcpy_desc(display_info *p, alt_u8 frame, sprite s, void * img, int t_width, int t_height) {

	alt_sgdma_descriptor * desc = (alt_sgdma_descriptor *) malloc(sizeof(alt_sgdma_descriptor)*s.height);

	int i;
	for(i=0; i < s.height; i++) {
		// One SGDMA descriptor per line
		alt_u32 * src_pos = (alt_u32 *) img + i*t_width;
		alt_u32 * dest_pos = (alt_u32 *) p->frame_buffer[frame+1] + (s.y+i)*DISPLAY_MAX_WIDTH + s.x;
		alt_u32 c_size =  s.width*sizeof(alt_u32);

		alt_avalon_sgdma_construct_mem_to_mem_desc(desc+i, (i == s.height-1)? 0: (desc+i+1), src_pos, dest_pos, c_size, 0, 0);
	}

	return desc;
}

void display_sprite_init(display_info * p, sprite * s, alt_u16 x, alt_u16 y, alt_u16 width, alt_u16 height, alt_u32 * base, alt_u8 * alpha, alt_u8 type) {

	// Initializes structure
	s->x = x;
	s->y = y;
	s->height = height;
	s->width = width;
	s->img_base = base;
	s->alpha = alpha;
	s->type = type;

	// If type is not null, it represents hardware sprite to be used
	if(type) {
		// Initialize image frame
		IOWR(p->sprite_base[s->type-1], 0, 0);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_BASE, (alt_u32) s->img_base);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_WORDS, s->width*s->height);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_COLOR_PATTERN, s->width*s->height);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_WIDTH, s->width);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_HEIGHT, s->height);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_INTERLACE, 1);
		IOWR(p->sprite_base[s->type-1], 0, 1);

		// Initialize alpha frame
		IOWR(p->alpha_base[s->type-1], 0, 0);
		IOWR(p->alpha_base[s->type-1], DISPLAY_FRAME0_BASE, (alt_u32) s->alpha);
		IOWR(p->alpha_base[s->type-1], DISPLAY_FRAME0_WORDS, s->width*s->height/4);
		IOWR(p->alpha_base[s->type-1], DISPLAY_FRAME0_COLOR_PATTERN, s->width*s->height);
		IOWR(p->alpha_base[s->type-1], DISPLAY_FRAME0_WIDTH, s->width);
		IOWR(p->alpha_base[s->type-1], DISPLAY_FRAME0_HEIGHT, s->height);
		IOWR(p->alpha_base[s->type-1], DISPLAY_FRAME0_INTERLACE, 1);
		IOWR(p->alpha_base[s->type-1], 0, 1);
	}

}

void display_sprite_change(display_info * p, sprite * s, alt_u16 width, alt_u16 height, alt_u32 * img_base, alt_u8* alpha_base) {

	s->img_base = img_base;
	s->alpha = alpha_base;
	s->height = height;
	s->width = width;

	// If type is not null, it represents hardware sprite to be used
	if(s->type) {

		// Image frame
		IOWR(p->sprite_base[s->type-1], 0, 0);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_BASE, (alt_u32) s->img_base);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_WORDS, s->width*s->height);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_COLOR_PATTERN, s->width*s->height);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_WIDTH, s->width);
		IOWR(p->sprite_base[s->type-1], DISPLAY_FRAME0_HEIGHT, s->height);
		IOWR(p->sprite_base[s->type-1], 0, 1);

		// Alpha frame
		IOWR(p->alpha_base[s->type-1], 0, 0);
		IOWR(p->alpha_base[s->type-1], DISPLAY_FRAME0_BASE, (alt_u32) s->alpha);
		IOWR(p->alpha_base[s->type-1], DISPLAY_FRAME0_WORDS, s->width*s->height/4);
		IOWR(p->alpha_base[s->type-1], DISPLAY_FRAME0_COLOR_PATTERN, s->width*s->height);
		IOWR(p->alpha_base[s->type-1], DISPLAY_FRAME0_WIDTH, s->width);
		IOWR(p->alpha_base[s->type-1], DISPLAY_FRAME0_HEIGHT, s->height);
		IOWR(p->alpha_base[s->type-1], 0, 1);
	}

}
