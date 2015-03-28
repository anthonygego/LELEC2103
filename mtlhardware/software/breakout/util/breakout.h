#ifndef BREAKOUT_H_
#define BREAKOUT_H_

#include <includes.h>

#include "mtc.h"
#include "pic32.h"
#include "display.h"
#include "adxl345.h"

typedef struct {
	pic32_info     * pic32_handle;
	mtc_info       * mtc_handle;
	display_info   * display_handle;
	adxl345_info   * adxl345_handle;
} peripherals;

typedef struct {
	peripherals periph;
} game_struct;

#endif /* BREAKOUT_H_ */
