#ifndef SPRITE_H_
#define SPRITE_H_

#include <alt_types.h>

typedef struct {
	alt_u32 x;
	alt_u32 y;
	alt_u32 * img_base;
	alt_u8 type; // hard or soft
} sprite;

#endif /* SPRITE_H_ */
