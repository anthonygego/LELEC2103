#ifndef SPRITE_H_
#define SPRITE_H_

#include <alt_types.h>

typedef struct {
	alt_u16 x;
	alt_u16 y;
	alt_u16 width;
	alt_u16 height;
	alt_u32 * img_base;
	alt_u32 alpha;
	alt_u32 type;
} sprite;

sprite * sprite_init(alt_u16 x, alt_u16 y, alt_u16 width, alt_u16 height, alt_u32 * base, alt_u32 alpha, alt_u32 type);

#endif /* SPRITE_H_ */
