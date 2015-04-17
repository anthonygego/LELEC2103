#include <io.h>
#include <sys/alt_cache.h>
#include "simpletext.h"

__inline__ void simpletext_alpha_blending(int x, int y, unsigned char alpha, unsigned char * color, display_info * display, alt_u8 as_sprite)
{
	unsigned char * background;
	if(as_sprite)
		background = (unsigned char *) &(display->frame_buffer[0][y][x]);
	else
		background = (unsigned char *) &(display->frame_buffer[!(display->displayed_frame)+1][y][x]);

	// these blended colors may need to be clipped to the maximum amounts the color depth supports
	unsigned int blended_red = ((color[2] * alpha) + (background[2] * (255 - alpha)))/255;
	unsigned int blended_green = ((color[1] * alpha) + (background[1] * (255 - alpha)))/255;
	unsigned int blended_blue = ((color[0] * alpha) + (background[0] * (255 - alpha)))/255;

	color[2] = (blended_red > 0xFF)? 0xFF: blended_red;
	color[1] = (blended_green > 0xFF)? 0xFF: blended_green;
	color[0] = (blended_blue > 0xFF)? 0xFF: blended_blue;
}

__inline__ void simpletext_print_char(display_info * display, int x, int y, int color, char character, struct abc_font_struct font[], alt_u8 as_sprite)
{
	alt_u8 space = 0;

	if(character==' ') {
		space = 1;
		character = '-';
	}

	// Assign the pointer of the font bitmap
	unsigned char * alpha = font[character-33].char_alpha_map;

	int i, j;
	for(i = 0; i < font[character-33].bounds_height; i++) {
		for (j = 0; j < font[character-33].bounds_width; j++) {
			unsigned int new_color = color;

			if(space) {
				// Update pixel value
				display->frame_buffer[!(display->displayed_frame)+1][y+i][x+j] = display->frame_buffer[0][y+i][x+j];
			}
			else {
				// Making alpha blending
				simpletext_alpha_blending ((x+j), (y+i), *alpha, (unsigned char*) &new_color, display, as_sprite);

				// Update pixel value
				display->frame_buffer[!(display->displayed_frame)+1][y+i][x+j] = new_color;

				alpha++;
			}

		}
	}
}

void simpletext_print(display_info * display, int x, int y, int color , font_struct font[], char string[], alt_u8 as_sprite)
{
	int i;
	int original_x = x;

	// Print until we hit the '\0' char.
	for (i=0; string[i]; i++) {

		//Handle newline char here.
		if (string[i] == '\n') {
			x = original_x;
			y += font['|' - 33].bounds_height;  // we'll use "|" to add the line to line spacing
		} else {
			// Lay down that character and increment our offsets.

			if((string[i] != 32) && (string[i] != '\t')) {
				simpletext_print_char(display, x, y, color, string[i], font, as_sprite);
				x += font[string[i] - 33].bounds_width;
			}
			else
			{
				if(as_sprite)
					simpletext_print_char(display, x, y, color, ' ', font, as_sprite);
				x += ((string[i] == 32)+2*(string[i] == '\t'))*font[45 - 33].bounds_width;
			}
		}
	}

	alt_dcache_flush_all();
}

