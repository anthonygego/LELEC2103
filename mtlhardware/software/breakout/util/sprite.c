#include <stdlib.h>
#include <alt_types.h>

#include "sprite.h"

sprite * sprite_init(alt_u16 x, alt_u16 y, alt_u16 width, alt_u16 height, alt_u32 * base, alt_u8 texture, alt_u32 alpha)
{
	sprite *p = malloc(sizeof(sprite));
	p->x = x;
	p->y = y;
	p->height = height;
	p->width = width;
	p->img_base = base;
	p->texture = texture;
	p->alpha = alpha;
	return p;
}
