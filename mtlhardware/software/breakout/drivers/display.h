#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <includes.h>
#include <alt_types.h>
#include <altera_avalon_sgdma.h>
#include <altera_avalon_sgdma_regs.h>
#include <altera_avalon_sgdma_descriptor.h>

#include "sprite.h"
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

#define DISPLAY_MAX_HEIGHT			  480
#define DISPLAY_MAX_WIDTH			  800

#define DISPLAY_DESCS_QUEUE_SIZE      256

typedef struct
{
    alt_u32 	    DISPLAY_BASE;
    alt_u32 	    frame_buffer [3][DISPLAY_MAX_HEIGHT][DISPLAY_MAX_WIDTH];
    alt_u32 	    desc_current;
    alt_u8  	    displayed_frame;
    alt_u8 		    alt_frame;
    queue 		  * desc_queue[2];
    queue 		  * switch_queue;
    alt_sgdma_dev * sgdma;
} display_info;

display_info* display_init(alt_u32 DISPLAY_BASE, const char * sgdma_name, alt_avalon_sgdma_callback sgdma_callback, void *sgdma_context);
void   		  display_uninit(display_info* p);
void          display_go(display_info* p, alt_u8 bGo);
void          display_switch_frame(display_info* p);
void 		  display_frame_done(display_info *p);
void          display_move_sprite(display_info *p, sprite *s, alt_u8 end_frame, int to_x, int to_y);
void          display_remove_sprite(display_info *p, sprite *s, alt_u8 end_frame);
void          display_add_sprite(display_info *p, sprite *s, alt_u8 end_frame);
void          display_push_desc(display_info* p, alt_sgdma_descriptor * desc, alt_u8 frame, alt_u8 end_frame);
alt_sgdma_descriptor * display_imgcpy_desc(display_info *p, alt_u8 frame, sprite * s, void * img, int t_width, int t_height);
alt_sgdma_descriptor * display_texcpy_desc(display_info *p, alt_u8 frame, void * tex, int x, int y, int c_width, int c_height, int t_size);

#endif /* DISPLAY_H_ */
