#ifndef PIC32_H_
#define PIC32_H_

#include <alt_types.h>

#define CYCLONE_RPC_MIWI		0
#define CYCLONE_RPC_FILE		1
#define CYCLONE_RPC_INFO        2

#define CYCLONE_TXDATA          0
#define CYCLONE_RXDATA          1
#define CYCLONE_TXSTATUS        2
#define CYCLONE_RXSTATUS        3

#define CYCLONE_ACK_MASK        128
#define CYCLONE_START_MASK      64
#define CYCLONE_END_MASK        32
#define CYCLONE_SIZE_MASK       16
#define CYCLONE_INIT_MASK       8
#define CYCLONE_TYPE_MASK		4

typedef struct
{
	size_t   size;
	size_t   cnt;
	alt_u8   can_send;
	alt_u8   transfer_done;
	alt_u8   type;
	char   * buffer;
} txrx_state;

typedef struct {
    alt_u32      PIC_BASE;
    alt_u32      INT1_BASE;
    alt_u32      INT2_BASE;
    alt_u32      INT2_IRQ_NUM;
    alt_u32      INT2_IRQ_CONTROLLER;
    txrx_state * state;
} pic32_info;

pic32_info*   pic32_init   (alt_u32 PIC_BASE, alt_u32 INT1_BASE, alt_u32 INT2_BASE, alt_u32 INT2_IRQ_CONTROLLER, alt_u32 INT2_IRQ_NUM);
void          pic32_uninit (pic32_info* p);
void          pic32_send   (pic32_info* p, char * data, size_t length, alt_u8 type);
void          pic32_sendrpc(pic32_info* p, char * msg, size_t length, alt_u8 rpc);
alt_u8        pic32_receive(pic32_info* p, char ** buffer, size_t * length, alt_u8 type);

#endif /* PIC32_H_ */
