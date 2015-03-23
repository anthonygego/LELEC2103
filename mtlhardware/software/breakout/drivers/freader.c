#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <sys/alt_cache.h>

#include <freader.h>

freader_info* freader_init(alt_u32 FREADER_BASE, alt_u32 width, alt_u32 height) {
	// Initialize frame reader info
    freader_info *p = malloc(sizeof(freader_info));

    // Copy information
    p->FREADER_BASE = FREADER_BASE;
    p->current_frame = 0;
    p->width = width;
    p->height = height;

    freader_go(p, 0);

    // Configure frame 0
	IOWR(FREADER_BASE, FREADER_FRAME0_BASE, (alt_u32)p->frame_buffer[0].lin);
	IOWR(FREADER_BASE, FREADER_FRAME0_WORDS, width*height);
	IOWR(FREADER_BASE, FREADER_FRAME0_COLOR_PATTERN, width*height);
	IOWR(FREADER_BASE, FREADER_FRAME0_WIDTH, width);
	IOWR(FREADER_BASE, FREADER_FRAME0_HEIGHT, height);
	IOWR(FREADER_BASE, FREADER_FRAME0_INTERLACE, 0);

	// Configure frame 1
	IOWR(FREADER_BASE, FREADER_FRAME1_BASE, (alt_u32)p->frame_buffer[1].lin);
	IOWR(FREADER_BASE, FREADER_FRAME1_WORDS, width*height);
	IOWR(FREADER_BASE, FREADER_FRAME1_COLOR_PATTERN, width*height);
	IOWR(FREADER_BASE, FREADER_FRAME1_WIDTH, width);
	IOWR(FREADER_BASE, FREADER_FRAME1_HEIGHT, height);
	IOWR(FREADER_BASE, FREADER_FRAME1_INTERLACE, 0);

    freader_select_frame(p, p->current_frame);

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

void freader_select_frame(freader_info* p, alt_u8 index) {
	p->current_frame = index;
    IOWR(p->FREADER_BASE, 3, index);
    alt_dcache_flush_all();
}
