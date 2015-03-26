#ifndef DMA_H_
#define DMA_H_

#include <altera_avalon_sgdma.h>
#include <altera_avalon_sgdma_regs.h>
#include <altera_avalon_sgdma_descriptor.h>

#include "freader.h"

typedef struct alt_sgdma_dev sgdma_info;

#define SGDMA_MAX_BLOCK_SIZE 32768

sgdma_info * sgdma_init(const char * NAME);
void sgdma_uninit(sgdma_info * p);
void sgdma_memcpy(sgdma_info * p, void * dest, void * src, int size);
void sgdma_imgcpy(sgdma_info * p, void * img, void * buffer, int x, int y, int cwidth, int cheight, int twidth, int theight);

#endif /* DMA_H_ */
