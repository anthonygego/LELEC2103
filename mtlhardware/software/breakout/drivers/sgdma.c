#include <stdlib.h>
#include <stdio.h>
#include <alt_types.h>

#include <altera_avalon_sgdma.h>
#include <altera_avalon_sgdma_regs.h>
#include <altera_avalon_sgdma_descriptor.h>

#include "sgdma.h"

void sgdma_isr(void *isr_context)
{
	//sgdma_info * p = (sgdma_info *) isr_context;
	printf("DMA operation finished\n!");
}

sgdma_info * sgdma_init(const char * NAME)
{
	sgdma_info * p = alt_avalon_sgdma_open(NAME);
	alt_u32 control = IORD_ALTERA_AVALON_SGDMA_CONTROL(p->base);
	IOWR_ALTERA_AVALON_SGDMA_CONTROL(p->base, control | ALTERA_AVALON_SGDMA_CONTROL_IE_CHAIN_COMPLETED_MSK);
	alt_avalon_sgdma_register_callback(p, sgdma_isr, p->chain_control, p);
	return p;
}

void sgdma_uninit(sgdma_info * p) {
	if(p)
		free(p);
}

void sgdma_memcpy(sgdma_info *dma, void *dest, void *src, int size){

    // Allocate descriptors list
    int nb_desc = (size+SGDMA_MAX_BLOCK_SIZE-1)/SGDMA_MAX_BLOCK_SIZE;
    alt_sgdma_descriptor *desc = (alt_sgdma_descriptor *) malloc(sizeof(alt_sgdma_descriptor)*nb_desc);

    // Initialize loop information
    int i;
    int remaining_size = size;
    char *dest_block = dest;
    char *src_block = src;

    // Compute the different descriptors
    for(i=0; remaining_size > 0; i++)
    {
    	// Compute descriptor block size
    	int nBlockSize = SGDMA_MAX_BLOCK_SIZE > remaining_size ? remaining_size : SGDMA_MAX_BLOCK_SIZE;
    	remaining_size -= nBlockSize;

    	// Construct descriptor itself
        alt_avalon_sgdma_construct_mem_to_mem_desc(desc+i, (remaining_size == 0)? 0: (desc+i+1), (alt_u32 *) src_block, (alt_u32 *) dest_block, nBlockSize, 0, 0);

        // Move pointers forward
        dest_block += nBlockSize;
        src_block += nBlockSize;
    }

    // Start synchronous transfer (memcpy is synchronous)
    alt_avalon_sgdma_do_sync_transfer(dma, desc);

    // Free resource
    free(desc);
}
