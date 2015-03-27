#ifndef SPRITE_H_
#define SPRITE_H_

#include <alt_types.h>

typedef enum {
	SOFTWARE,
	HARDWARE
} sprite_type;

typedef struct {
	alt_u16 x;
	alt_u16 y;
	alt_u16 width;
	alt_u16 height;
	alt_u32 * img_base;
	sprite_type type; // hard or soft
} sprite;

sprite * sprite_init(alt_u16 x, alt_u16 y, alt_u16 width, alt_u16 height, alt_u32 * base, sprite_type type);

#endif /* SPRITE_H_ */
