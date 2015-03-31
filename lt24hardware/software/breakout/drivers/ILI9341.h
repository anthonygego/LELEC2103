#ifndef ILI9341_H_
#define ILI9341_H_

#include <alt_types.h>

////////////// configuration //////////////
#define X_RES   SCREEN_WIDTH
#define Y_RES   SCREEN_HEIGHT

#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	320

typedef struct{


    // for altera vip library
    int color_depth;
    int width;
    int height;
    int bytes_per_pixel;
    int interlace;
} alt_video_display;

typedef struct {
    alt_u32  BASE;
    alt_u32  RESET_N_BASE;
} lcd_info;


lcd_info * lcd_init(alt_u32 BASE, alt_u32 RESET_N_BASE);
void lcd_clear(lcd_info *p, alt_u16 Color);
void lcd_draw_point(lcd_info *p, alt_u16 x,alt_u16 y,alt_u16 color );

#endif /* ILI9341_H_ */
