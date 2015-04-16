#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <includes.h>
#include <alt_types.h>
#include <altera_avalon_sgdma.h>

#include "queue.h"

#define SGDMA_MAX_BLOCK_SIZE          32768

#define DISPLAY_FRAME0_BASE           4
#define DISPLAY_FRAME0_WORDS          5
#define DISPLAY_FRAME0_COLOR_PATTERN  6
#define DISPLAY_FRAME0_WIDTH          8
#define DISPLAY_FRAME0_HEIGHT         9
#define DISPLAY_FRAME0_INTERLACE      10

#define DISPLAY_FRAME1_BASE           11
#define DISPLAY_FRAME1_WORDS          12
#define DISPLAY_FRAME1_COLOR_PATTERN  13
#define DISPLAY_FRAME1_WIDTH          15
#define DISPLAY_FRAME1_HEIGHT         16
#define DISPLAY_FRAME1_INTERLACE      17

#define MIXER_LAYER0_X				  2
#define MIXER_LAYER0_Y				  3
#define MIXER_LAYER0_ACTIVE			  4

#define DISPLAY_MAX_HEIGHT			  480
#define DISPLAY_MAX_WIDTH			  800

#define DISPLAY_DESCS_QUEUE_SIZE      2048

typedef struct
{
	// Address to peripherals
    alt_u32 	    bg_frame_base;
    alt_u32			mixer_base;
    alt_u32			sprite_base   [2];
    alt_u32			alpha_base    [2];

    // Image buffers
    alt_u32 	    frame_buffer  [4][DISPLAY_MAX_HEIGHT][DISPLAY_MAX_WIDTH];
    alt_u32			bricks_img    [4][1000];
    alt_u32			wall_vert_img [4400];
    alt_u32			wall_horiz_img[8000];

    // Switch frame logic
    alt_u8  	    displayed_frame;
    queue 		  * desc_queue[2];
    alt_sgdma_dev * sgdma;
} display_info;

typedef struct {
	alt_u16   x;
	alt_u16   y;
	alt_u16   width;
	alt_u16   height;
	alt_u32 * img_base;
	alt_u8  * alpha;
	alt_u8    type;
} sprite;

display_info* display_init(alt_u32 mixer_base, alt_u32 bg_frame_base, alt_u32 sprite0_base, alt_u32 sprite1_base, alt_u32 sprite0_alpha, alt_u32 sprite1_alpha, const char * sgdma_name);
sprite *      display_sprite_init(display_info * p, alt_u16 x, alt_u16 y, alt_u16 width, alt_u16 height, alt_u32 * base, alt_u8 * alpha, alt_u8 type);

void   		  display_uninit(display_info* p);
void          display_go(display_info* p, alt_u8 bGo);
void          display_switch_frame(display_info* p);
void 		  display_frame_done(display_info *p);
void          display_move_sprite(display_info *p, sprite *s, int to_x, int to_y);
void          display_remove_sprite(display_info *p, sprite *s);
void          display_add_sprite(display_info *p, sprite *s);
void          display_end_frame(display_info *p);
void          display_push_desc(display_info* p, alt_sgdma_descriptor * desc, alt_u8 frame);

#endif /* DISPLAY_H_ */
