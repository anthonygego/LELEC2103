#ifndef PIC32_H_
#define PIC32_H_

#include <alt_types.h>

#define CYCLONE_RPC_MIWI		0
#define CYCLONE_RPC_FILE		1

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

typedef struct pic32_txrx_struct
{
	size_t   size;
	size_t   cnt;
	alt_u8   can_send;
	alt_u8   transfer_done;
	alt_u8   type;
	char   * buffer;
} pic32_txrx_state;

void   pic32_init   ();
void   pic32_send   (char * data, size_t length, alt_u8 type);
void   pic32_sendrpc(char * msg, size_t length, alt_u8 rpc);
alt_u8 pic32_receive(char ** buffer, size_t * length, alt_u8 type);

#endif /* PIC32_H_ */
