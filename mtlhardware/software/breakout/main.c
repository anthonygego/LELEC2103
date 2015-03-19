#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <includes.h>
#include <alt_types.h>

#include "pic32.h"
#include "mtc.h"

#include "mpack.h"
#include "console.h"
#include "rpc.h"

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
	pic32_init();
	mtc_info * mtc_handle = mtc_init(MULTI_TOUCH_BASE, MULTI_TOUCH_IRQ_INTERRUPT_CONTROLLER_ID, MULTI_TOUCH_IRQ);

	// Welcome message
	printf("Breakout console\n");

	// Create RPC task
	OSTaskCreateExt(rpc_task,
				  NULL,
				  (void *)&rpc_task_stk[TASK_STACKSIZE-1],
				  RPC_TASK_PRIORITY,
				  RPC_TASK_PRIORITY,
				  rpc_task_stk,
				  TASK_STACKSIZE,
				  NULL,
				  0);

	// Create console task
	OSTaskCreateExt(console_task,
			      mtc_handle,
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
