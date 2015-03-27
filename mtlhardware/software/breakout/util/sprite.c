#include <stdlib.h>
#include <alt_types.h>

#include "sprite.h"

sprite * sprite_init(alt_u16 x, alt_u16 y, alt_u16 width, alt_u16 height, alt_u32 * base, sprite_type type)
{
	sprite *p = malloc(sizeof(sprite));
	p->x = x;
	p->y = y;
	p->height = height;
	p->width = width;
	p->img_base = base;
	p->type = type;

	return p;
}
