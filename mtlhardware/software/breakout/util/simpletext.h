#ifndef SIMPLETEXT_H_
#define SIMPLETEXT_H_

#include "display.h"

extern struct abc_font_struct tahomabold_32[];

void simpletext_print(display_info * display, int x, int y, int color, font_struct font[], char string[]);

#endif /* SIMPLETEXT_H_ */
