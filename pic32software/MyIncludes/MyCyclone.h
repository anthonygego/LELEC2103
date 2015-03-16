/*******************************************************************************
* Header file for MyCyclone                                                    *
*******************************************************************************/

// SPI frame = 1 opcode (R/W bit + 7-bit address) + 1 data byte

#ifndef MYCYCLONE_H
#define	MYCYCLONE_H

#define CYCLONE_TXDATA          0
#define CYCLONE_RXDATA          1
#define CYCLONE_TXSTATUS        2
#define CYCLONE_RXSTATUS        3

#define CYCLONE_ACK_MASK        128
#define CYCLONE_START_MASK      64
#define CYCLONE_END_MASK        32
#define CYCLONE_SIZE_MASK       16
#define CYCLONE_INIT_MASK       8
#define CYCLONE_TYPE_MASK       4

typedef struct pic32_txrx_struct
{
	size_t   size;
	size_t   cnt;
	BOOL     can_send;
	BOOL     transfer_done;
        BOOL     type;
	BYTE   * buffer;
} pic32_txrx_state;

/*******************************************************************************
* Functions Prototypes                                                         *
*******************************************************************************/

void            MyCyclone_Init(void);
void            MyCyclone_Send(BYTE * data, size_t length, BOOL type);
BOOL            MyCyclone_Receive(BYTE ** buffer, size_t * length, BOOL type);
int             MyCyclone_SendFile(char * filename);
void            MyCyclone_Task(void);

/*******************************************************************************
* Global Variables for MyCyclone Functions                                     *
*******************************************************************************/

#ifdef   MyCYCLONE

#endif

#endif	/* MYCYCLONE_H */

