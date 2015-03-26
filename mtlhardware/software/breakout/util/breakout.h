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
	OS_EVENT	   * pic32_sem;
	mtc_info       * mtc_handle;
	OS_EVENT       * mtc_sem;
	freader_info   * freader_handle;
	OS_EVENT       * freader_sem;
	sgdma_info     * sgdma_handle;
	OS_EVENT	   * sgdma_sem;
	adxl345_info   * adxl345_handle;
	OS_EVENT	   * adxl345_sem;
} game_state;

#endif /* BREAKOUT_H_ */
