#ifndef ILI9341_H_
#define ILI9341_H_

#include <alt_types.h>

typedef struct {
    alt_u32  BASE;
    alt_u32  RESET_N_BASE;
} lcd_info;


lcd_info * lcd_init(alt_u32 BASE, alt_u32 RESET_N_BASE);
void lcd_clear(lcd_info *p, alt_u16 Color);
void lcd_draw_point(lcd_info *p, alt_u16 x,alt_u16 y,alt_u16 color );

#endif /* ILI9341_H_ */
