#ifndef BREAKOUT_H_
#define BREAKOUT_H_

#include "mtc.h"
#include "pic32.h"

typedef struct {
	pic32_info * pic32_handle;
	mtc_info   * mtc_handle;
} game_state;

#endif /* BREAKOUT_H_ */
