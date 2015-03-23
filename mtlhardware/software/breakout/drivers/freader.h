#ifndef FREADER_H_
#define FREADER_H_

#include <alt_types.h>

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

typedef union {
	int tab[FREADER_MAX_HEIGHT][FREADER_MAX_WIDTH];
	int lin[FREADER_MAX_HEIGHT*FREADER_MAX_WIDTH];
} graphics_buffer;

typedef struct{
    alt_u32 FREADER_BASE;
    graphics_buffer frame_buffer[2];
    alt_u8  current_frame;
    int width;
    int height;
} freader_info;

freader_info* freader_init(alt_u32 FREADER_BASE, alt_u32 width, alt_u32 height);
void   		  freader_uninit(freader_info* p);
void          freader_go(freader_info* p, alt_u8 bGo);
void          freader_select_frame(freader_info* p, alt_u8 FrameIndex);

#endif /* FREADER_H_ */
