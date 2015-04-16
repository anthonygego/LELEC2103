#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <alt_types.h>
#include <system.h>
#include <sys/alt_irq.h>
#include <altera_avalon_pio_regs.h>
#include "pic32.h"
#include "mpack.h"

void pic32_sendack(pic32_info * p)
{
	while(!p->state->can_send);
	IOWR(p->PIC_BASE, CYCLONE_RXSTATUS, CYCLONE_ACK_MASK);
	IOWR(p->INT1_BASE, 0, 1);
	IOWR(p->INT1_BASE, 0, 0);
}

void pic32_isr(void *isr_context)
{
	pic32_info *p = (pic32_info *) isr_context;

	// Clean interrupt
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(p->INT2_BASE, 1);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(p->INT2_BASE);

	int status = IORD(p->PIC_BASE,CYCLONE_TXSTATUS);

	if(status & CYCLONE_INIT_MASK)
	{
		p->state->size = 0;
		p->state->cnt = 0;
		p->state->can_send = 1;
		p->state->transfer_done = 0;
		p->state->type = ((status & CYCLONE_TYPE_MASK) > 0);
		p->state->buffer = NULL;
		pic32_sendack(p);
	}
	else if(status & CYCLONE_ACK_MASK)
		p->state->can_send = 1;
	else
	{
		if(status & CYCLONE_SIZE_MASK)
			p->state->size = (p->state->size << 8) + IORD(p->PIC_BASE,CYCLONE_TXDATA);
		else
		{

			if(status & CYCLONE_START_MASK)
			{
				p->state->buffer = malloc(sizeof(char)*(p->state->size));
				p->state->cnt = 0;
			}

			if(p->state->buffer)
				p->state->buffer[p->state->cnt++] = IORD(p->PIC_BASE,CYCLONE_TXDATA);

			if(status & CYCLONE_END_MASK)
				p->state->transfer_done = 1;

		}
		pic32_sendack(p);
	}
}

pic32_info* pic32_init(alt_u32 PIC_BASE, alt_u32 INT1_BASE, alt_u32 INT2_BASE, alt_u32 INT2_IRQ_CONTROLLER, alt_u32 INT2_IRQ_NUM)
{
	pic32_info *p = (pic32_info *) malloc(sizeof(pic32_info));
	p->PIC_BASE = PIC_BASE;
	p->INT1_BASE = INT1_BASE;
	p->INT2_BASE = INT2_BASE;
	p->INT2_IRQ_CONTROLLER = INT2_IRQ_CONTROLLER;
	p->INT2_IRQ_NUM = INT2_IRQ_NUM;
	p->state = (txrx_state *) malloc(sizeof(txrx_state));
	p->sem = OSSemCreate(1);

	// Enable  interrupt.
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(p->INT2_BASE, 0x1);

	// Reset the edge capture register.
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(p->INT2_BASE, 0x1);

	// Register interrupt
	alt_ic_isr_register(p->INT2_IRQ_CONTROLLER, p->INT2_IRQ_NUM, pic32_isr, p, 0x0);

	p->state->size = 0;
	p->state->cnt = 0;
	p->state->can_send = 1;
	p->state->transfer_done = 0;
	p->state->type = 0;
	p->state->buffer = NULL;

	return p;
}

void pic32_uninit(pic32_info* p)
{
	if(p)
	{
		alt_u8 err;
		OSSemDel(p->sem, OS_DEL_ALWAYS, &err);
		free(p->state);
		free(p);
	}
}

alt_u8 pic32_receive(pic32_info* p, char ** buffer, size_t * length, alt_u8 type)
{
    if(!(p->state->transfer_done && p->state->type == type))
        return 0;
    else
    {
        p->state->transfer_done = 0;
        *buffer = p->state->buffer;
        *length = p->state->size;
        return 1;
    }
}

void pic32_send(pic32_info* p, char * data, size_t length, alt_u8 type)
{
    int i;
    while(!p->state->can_send);
    IOWR(p->PIC_BASE, CYCLONE_RXSTATUS, CYCLONE_INIT_MASK | (type ? CYCLONE_TYPE_MASK : 0));
    p->state->can_send = 0;
    IOWR(p->INT1_BASE, 0, 1);
    IOWR(p->INT1_BASE, 0, 0);
    while(!p->state->can_send);

    for(i=sizeof(size_t)-1; i >=0; i--)
    {
        while(!p->state->can_send);
        IOWR(p->PIC_BASE, CYCLONE_RXDATA, (length >> 8*i) & 0xff);
        IOWR(p->PIC_BASE, CYCLONE_RXSTATUS, CYCLONE_SIZE_MASK | (type ? CYCLONE_TYPE_MASK : 0));
        p->state->can_send = 0;
        IOWR(p->INT1_BASE, 0, 1);
        IOWR(p->INT1_BASE, 0, 0);
        while(!p->state->can_send);
    }

    for(i=0; i < length; i++)
    {
        while(!p->state->can_send);
        IOWR(p->PIC_BASE, CYCLONE_RXDATA, data[i]);
        IOWR(p->PIC_BASE, CYCLONE_RXSTATUS, (i==0 ? CYCLONE_START_MASK : 0) | (i==length-1 ? CYCLONE_END_MASK : 0) | (type ? CYCLONE_TYPE_MASK : 0) );
        p->state->can_send = 0;
        IOWR(p->INT1_BASE, 0, 1);
        IOWR(p->INT1_BASE, 0, 0);
        while(!p->state->can_send);
    }

}

void pic32_sendrpc(pic32_info* p, char * msg, size_t length, alt_u8 rpc)
{
	char * buffer = malloc(sizeof(char)*(length+10));

	mpack_writer_t writer;
	mpack_writer_init_buffer(&writer, buffer, length+10);
	mpack_write_u8(&writer, rpc);
	mpack_write_bin(&writer, msg, length);

	size_t count = mpack_writer_buffer_used(&writer);
	mpack_writer_destroy(&writer);

	pic32_send(p, buffer, count, 1);

	free(buffer);
}
