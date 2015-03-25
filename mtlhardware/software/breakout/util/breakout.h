#ifndef BREAKOUT_H_
#define BREAKOUT_H_

#include <includes.h>

#include "mtc.h"
#include "pic32.h"
#include "freader.h"
#include "sgdma.h"

typedef struct {
	pic32_info     * pic32_handle;
	OS_EVENT	   * pic32_sem;
	mtc_info       * mtc_handle;
	OS_EVENT       * mtc_sem;
	freader_info   * freader_handle;
	OS_EVENT       * freader_sem;
	sgdma_info     * sgdma_handle;
} game_state;

#endif /* BREAKOUT_H_ */
