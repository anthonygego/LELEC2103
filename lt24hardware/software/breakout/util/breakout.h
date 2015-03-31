#ifndef BREAKOUT_H_
#define BREAKOUT_H_

#include "pic32.h"
#include "ILI9341.h"
#include "touch_spi.h"

typedef enum {
	ADD_LIFE = 0,
	REMOVE_LIFE = 1,
	SWITCH_PADDLE_SIZE = 2,
	ADD_BALL = 3,
	SPEED_DOWN = 4,
	SPEED_UP = 5
} game_event;

typedef struct {
	pic32_info   * pic32_handle;
	lcd_info     * lcd_handle;
	TOUCH_HANDLE * touch_handle;
} game_state;

#endif /* BREAKOUT_H_ */
