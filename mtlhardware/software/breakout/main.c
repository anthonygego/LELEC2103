#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <includes.h>
#include <alt_types.h>

#include "pic32.h"
#include "mtc.h"

#include "console.h"
#include "rpc.h"
#include "graphics.h"
#include "game.h"

#include "mpack.h"
#include "breakout.h"

/* Definition of Task Stacks */
#define     TASK_STACKSIZE       2048
OS_STK      graphics_task_stk    [TASK_STACKSIZE];
OS_STK      game_task_stk        [TASK_STACKSIZE];
OS_STK      game_status_task_stk [TASK_STACKSIZE];
OS_STK      rpc_task_stk         [TASK_STACKSIZE];
OS_STK      console_task_stk     [TASK_STACKSIZE];


/* Definition of Task Priorities */

#define GRAPHICS_TASK_PRIORITY     1
#define GAME_TASK_PRIORITY         2
#define GAME_STATUS_TASK_PRIORITY  3
#define RPC_TASK_PRIORITY          4
#define CONSOLE_TASK_PRIORITY      5

int main(void)
{

	// Initialize main structure
	game_struct game;

	// Initialize PIC32
	game.periph.pic32_handle = pic32_init(PIC32_BASE, PIC32_INT1_BASE, PIC32_INT2_BASE, PIC32_INT2_IRQ_INTERRUPT_CONTROLLER_ID, PIC32_INT2_IRQ);

	// Initialize MultiTouch Controller
	game.periph.mtc_handle = mtc_init(MULTI_TOUCH_BASE, MULTI_TOUCH_IRQ_INTERRUPT_CONTROLLER_ID, MULTI_TOUCH_IRQ);

	// Initialize Display
	game.periph.display_handle = display_init(VIDEO_MIXER_BASE, FRAME_BACKGROUND_BASE, FRAME_PADDLE_BASE, FRAME_BALL_BASE, ALPHA_PADDLE_BASE, ALPHA_BALL_BASE, SGDMA_NAME, graphics_isr, &game);

	// Initialize Accelerometer
	game.periph.adxl345_handle = adxl345_init(ADXL345_BASE);

	breakout_create_textures(game.periph.display_handle);
	breakout_clear_screen(game.periph.display_handle);
	game.state = NOGAME;

	// Create Graphics task
	OSTaskCreateExt(graphics_task,
				  (void *)&game,
				  (void *)&graphics_task_stk[TASK_STACKSIZE-1],
				  GRAPHICS_TASK_PRIORITY,
				  GRAPHICS_TASK_PRIORITY,
				  graphics_task_stk,
				  TASK_STACKSIZE,
				  NULL,
				  0);

	// Create Game task
	OSTaskCreateExt(game_task,
				  (void *)&game,
				  (void *)&game_task_stk[TASK_STACKSIZE-1],
				  GAME_TASK_PRIORITY,
				  GAME_TASK_PRIORITY,
				  game_task_stk,
				  TASK_STACKSIZE,
				  NULL,
				  0);

	// Create Game status task
	OSTaskCreateExt(game_status_task,
				  (void *)&game,
				  (void *)&game_status_task_stk[TASK_STACKSIZE-1],
				  GAME_STATUS_TASK_PRIORITY,
				  GAME_STATUS_TASK_PRIORITY,
				  game_status_task_stk,
				  TASK_STACKSIZE,
				  NULL,
				  0);

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
