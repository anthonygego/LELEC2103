#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <includes.h>
#include <alt_types.h>

#include "pic32.h"

#include "console.h"
#include "rpc.h"

#include "mpack.h"
#include "breakout.h"

/* Definition of Task Stacks */
#define     TASK_STACKSIZE       2048
OS_STK      rpc_task_stk         [TASK_STACKSIZE];
OS_STK      console_task_stk     [TASK_STACKSIZE];

/* Definition of Task Priorities */

#define RPC_TASK_PRIORITY          1
#define CONSOLE_TASK_PRIORITY      2

int main(void)
{
	// Initialize peripherals
	game_state game;
	game.pic32_handle = pic32_init(PIC32_BASE, PIC32_INT1_BASE, PIC32_INT2_BASE, PIC32_INT2_IRQ_INTERRUPT_CONTROLLER_ID, PIC32_INT2_IRQ);

	// Welcome message
	printf("Breakout console\n");

	// Create RPC task
	OSTaskCreateExt(rpc_task,
				  (void *)&game,
				  (void *)&rpc_task_stk[TASK_STACKSIZE-1],
				  RPC_TASK_PRIORITY,
				  RPC_TASK_PRIORITY,
				  rpc_task_stk,
				  TASK_STACKSIZE,
				  NULL,
				  0);

	// Create console task
	OSTaskCreateExt(console_task,
				  (void *)&game,
				  (void *)&console_task_stk[TASK_STACKSIZE-1],
				  CONSOLE_TASK_PRIORITY,
				  CONSOLE_TASK_PRIORITY,
				  console_task_stk,
				  TASK_STACKSIZE,
				  NULL,
				  0);

	// Start the OS scheduler
	OSStart();

	return 0;
}
