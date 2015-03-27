#ifndef BREAKOUT_H_
#define BREAKOUT_H_

#include <includes.h>

#include "mtc.h"
#include "pic32.h"
#include "freader.h"
#include "sgdma.h"
#include "adxl345.h"

typedef struct {
	pic32_info     * pic32_handle;
	mtc_info       * mtc_handle;
	freader_info   * freader_handle;
	sgdma_info     * sgdma_handle;
	adxl345_info   * adxl345_handle;
} peripherals;

typedef struct {
	peripherals periph;
} game_struct;

#endif /* BREAKOUT_H_ */
