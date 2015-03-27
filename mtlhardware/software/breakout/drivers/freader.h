#ifndef FREADER_H_
#define FREADER_H_

#include <includes.h>
#include <alt_types.h>

#include "sprite.h"
#include "queue.h"
#include "sgdma.h"


#define FREADER_FRAME0_BASE           4
#define FREADER_FRAME0_WORDS          5
#define FREADER_FRAME0_COLOR_PATTERN  6
#define FREADER_FRAME0_WIDTH          8
#define FREADER_FRAME0_HEIGHT         9
#define FREADER_FRAME0_INTERLACE      10

#define FREADER_FRAME1_BASE           11
#define FREADER_FRAME1_WORDS          12
#define FREADER_FRAME1_COLOR_PATTERN  13
#define FREADER_FRAME1_WIDTH          15
#define FREADER_FRAME1_HEIGHT         16
#define FREADER_FRAME1_INTERLACE      17

#define FREADER_MAX_HEIGHT			  480
#define FREADER_MAX_WIDTH			  800

#define FREADER_GEVENTS_QUEUE_SIZE    256
#define FREADER_DESCS_QUEUE_SIZE      256

typedef enum {
	ADD,
	REMOVE,
	MOVE
} graphical_event_type;

typedef struct{
    alt_u32 FREADER_BASE;
    alt_u32 frame_buffer [3][FREADER_MAX_HEIGHT][FREADER_MAX_WIDTH];
    alt_u8  current_frame;
    alt_u8  displayed_frame;
    alt_u32  desc_last;
    queue * gevent_queue;
    queue * desc_queue;
    OS_EVENT * gevent_sem;
    OS_EVENT * desc_sem;
    int width;
    int height;
} freader_info;

typedef struct {
	alt_u16 x;
	alt_u16 y;
	graphical_event_type type;
	sprite * sprite;
} graphical_event;

freader_info* freader_init(alt_u32 FREADER_BASE, alt_u32 width, alt_u32 height);
void   		  freader_uninit(freader_info* p);
void          freader_go(freader_info* p, alt_u8 bGo);
void          freader_switch_frame(freader_info* p);
void          freader_gevent(freader_info* p, alt_u16 x, alt_u16 y, graphical_event_type type, sprite * sprite);
void          freader_desc(freader_info* p, alt_sgdma_descriptor * desc);

int           freader_imgcpy_desc(freader_info *p, alt_sgdma_descriptor ** desc, alt_sgdma_descriptor * next, void * img, int x, int y, int c_width, int c_height, int t_width, int t_height);


#endif /* FREADER_H_ */
