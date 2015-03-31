#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <includes.h>
#include <alt_types.h>

#include "pic32.h"
#include "player2.h"

#include "console.h"
#include "rpc.h"
#include "touch_spi.h"

#include "mpack.h"
#include "breakout.h"

/* Definition of Task Stacks */
#define     TASK_STACKSIZE       2048
OS_STK      rpc_task_stk         [TASK_STACKSIZE];
OS_STK      console_task_stk     [TASK_STACKSIZE];
OS_STK      player2_task_stk     [TASK_STACKSIZE];

/* Definition of Task Priorities */

#define RPC_TASK_PRIORITY          1
#define PLAYER2_TASK_PRIORITY      2
#define CONSOLE_TASK_PRIORITY      3

int main(void)

{
	// Initialize peripherals
	game_state game;
	game.pic32_handle = pic32_init(PIC32_BASE, PIC32_INT1_BASE, PIC32_INT2_BASE, PIC32_INT2_IRQ_INTERRUPT_CONTROLLER_ID, PIC32_INT2_IRQ);
	game.lcd_handle = lcd_init(LCD_BASE, LCD_RESET_N_BASE);
	//game.touch_handle = Touch_Init(TOUCH_SPI_BASE, TOUCH_PEN_IRQ_N_BASE, TOUCH_PEN_IRQ_N_IRQ);


	// do touch handle ....

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

	// Create player2 task
	OSTaskCreateExt(player2_task,
				  (void *)&game,
				  (void *)&player2_task_stk[TASK_STACKSIZE-1],
				  PLAYER2_TASK_PRIORITY,
				  PLAYER2_TASK_PRIORITY,
				  player2_task_stk,
				  TASK_STACKSIZE,
				  NULL,
				  0);

	// Start the OS scheduler
	OSStart();

	return 0;
}
