#ifndef BREAKOUT_H_
#define BREAKOUT_H_

#include "pic32.h"
#include "ILI9341.h"

typedef struct {
	pic32_info * pic32_handle;
	lcd_info   * lcd_handle;
	//touch_info * touch_handle;
} game_state;

#endif /* BREAKOUT_H_ */
