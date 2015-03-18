#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <alt_types.h>
#include <system.h>
#include <sys/alt_irq.h>
#include <altera_avalon_pio_regs.h>
#include "pic32.h"
#include "mpack.h"

pic32_txrx_state pic32_state;

void pic32_sendack()
{
	while(!pic32_state.can_send);
	IOWR(PIC32_BASE, CYCLONE_RXSTATUS, CYCLONE_ACK_MASK);
	IOWR(PIC32_INT1_BASE, 0, 1);
	IOWR(PIC32_INT1_BASE, 0, 0);
}

void pic32_isr(void *isr_context)
{
	// Clean interrupt
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIC32_INT2_BASE, 1);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIC32_INT2_BASE);

	int status = IORD(PIC32_BASE,CYCLONE_TXSTATUS);

	if(status & CYCLONE_INIT_MASK)
	{
		pic32_state.size = 0;
		pic32_state.cnt = 0;
		pic32_state.can_send = 1;
		pic32_state.transfer_done = 0;
		pic32_state.type = ((status & CYCLONE_TYPE_MASK) > 0);
		pic32_state.buffer = NULL;
		pic32_sendack();
	}
	else if(status & CYCLONE_ACK_MASK)
		pic32_state.can_send = 1;
	else
	{
		if(status & CYCLONE_SIZE_MASK)
			pic32_state.size = (pic32_state.size << 8) + IORD(PIC32_BASE,CYCLONE_TXDATA);
		else
		{

			if(status & CYCLONE_START_MASK)
			{
				pic32_state.buffer = malloc(sizeof(char)*(pic32_state.size));
				pic32_state.cnt = 0;
			}

			pic32_state.buffer[pic32_state.cnt++] = IORD(PIC32_BASE,CYCLONE_TXDATA);

			if(status & CYCLONE_END_MASK)
				pic32_state.transfer_done = 1;

		}
		pic32_sendack();
	}
}

void pic32_init()
{
	// Enable all 4 button interrupts.
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIC32_INT2_BASE, 0x1);
	// Reset the edge capture register.
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIC32_INT2_BASE, 0x1);
	// Register interrupt
	alt_ic_isr_register(PIC32_INT2_IRQ_INTERRUPT_CONTROLLER_ID, PIC32_INT2_IRQ, pic32_isr, &pic32_state, 0x0);

	pic32_state.size = 0;
	pic32_state.cnt = 0;
	pic32_state.can_send = 1;
	pic32_state.transfer_done = 0;
	pic32_state.type = 0;
	pic32_state.buffer = NULL;
}

alt_u8 pic32_receive(char ** buffer, size_t * length, alt_u8 type)
{
    if(!(pic32_state.transfer_done && pic32_state.type == type))
        return 0;
    else
    {
        pic32_state.transfer_done = 0;
        *buffer = pic32_state.buffer;
        *length = pic32_state.size;
        return 1;
    }
}

void pic32_send(char * data, size_t length, alt_u8 type)
{
    int i;
    while(!pic32_state.can_send);
    IOWR(PIC32_BASE, CYCLONE_RXSTATUS, CYCLONE_INIT_MASK | (type ? CYCLONE_TYPE_MASK : 0));
    pic32_state.can_send = 0;
    IOWR(PIC32_INT1_BASE, 0, 1);
    IOWR(PIC32_INT1_BASE, 0, 0);
    while(!pic32_state.can_send);

    for(i=sizeof(size_t)-1; i >=0; i--)
    {
        while(!pic32_state.can_send);
        IOWR(PIC32_BASE, CYCLONE_RXDATA, (length >> 8*i) & 0xff);
        IOWR(PIC32_BASE, CYCLONE_RXSTATUS, CYCLONE_SIZE_MASK | (type ? CYCLONE_TYPE_MASK : 0));
        pic32_state.can_send = 0;
        IOWR(PIC32_INT1_BASE, 0, 1);
        IOWR(PIC32_INT1_BASE, 0, 0);
        while(!pic32_state.can_send);
    }

    for(i=0; i < length; i++)
    {
        while(!pic32_state.can_send);
        IOWR(PIC32_BASE, CYCLONE_RXDATA, data[i]);
        IOWR(PIC32_BASE, CYCLONE_RXSTATUS, (i==0 ? CYCLONE_START_MASK : 0) | (i==length-1 ? CYCLONE_END_MASK : 0) | (type ? CYCLONE_TYPE_MASK : 0) );
        pic32_state.can_send = 0;
        IOWR(PIC32_INT1_BASE, 0, 1);
        IOWR(PIC32_INT1_BASE, 0, 0);
        while(!pic32_state.can_send);
    }

}

void pic32_sendrpc(char * msg, size_t length, alt_u8 rpc)
{
	char * buffer = malloc(sizeof(char)*(length+10));

	mpack_writer_t writer;
	mpack_writer_init_buffer(&writer, buffer, length+10);
	mpack_write_u8(&writer, rpc);
	mpack_write_bin(&writer, msg, length);

	size_t count = mpack_writer_buffer_used(&writer);
	mpack_writer_destroy(&writer);

	pic32_send(buffer, count, 1);

	free(buffer);
}
