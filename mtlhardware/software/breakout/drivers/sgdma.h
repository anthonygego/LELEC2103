#ifndef DMA_H_
#define DMA_H_

#include <altera_avalon_sgdma.h>
#include <altera_avalon_sgdma_regs.h>
#include <altera_avalon_sgdma_descriptor.h>

typedef struct alt_sgdma_dev sgdma_info;

#define SGDMA_MAX_BLOCK_SIZE 32768

sgdma_info * sgdma_init(const char * NAME);
void sgdma_uninit(sgdma_info * p);
void sgdma_isr(void * isr_context);
void sgdma_memcpy(sgdma_info * dma, void * dest, void * src, int size);

#endif /* DMA_H_ */
