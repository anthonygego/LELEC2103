#ifndef BREAKOUT_H_
#define BREAKOUT_H_

#include <includes.h>
#include <system.h>
#include "mtc.h"
#include "pic32.h"
#include "display.h"
#include "adxl345.h"

#define IMG_BALL           0
#define ALPHA_BALL         400
#define IMG_PADDLE200      500
#define ALPHA_PADDLE200    4500
#define IMG_PADDLE100      5500
#define ALPHA_PADDLE100    7500

#define BALL_WIDTH         20
#define BALL_HEIGHT        20
#define NBR_BRICKS         168
#define SCORE_UNIT		   20
#define EVENT_QUEUE_SIZE   16

typedef enum {
	ADD_LIFE = 0,
	REMOVE_LIFE = 1,
	SWITCH_PADDLE_SIZE = 2,
	ADD_BRICK = 3,
	SPEED_DOWN = 4,
	SPEED_UP = 5
} game_event;

typedef enum {
	PAUSED = 0,
	NOT_MOVING = 1,
	BALL_MOVING = 2,
	NOGAME = 3,
	LOST = 4,
	WON = 5
} game_state;

typedef struct {
	alt_16 x;
	alt_16 y;
} vector;

typedef struct {
	sprite * s;
	vector   v;
} ball;

typedef struct {
	sprite * s;
	alt_u8   value;
	alt_u8   enabled;
} brick;

typedef struct {
	pic32_info     * pic32_handle;
	mtc_info       * mtc_handle;
	display_info   * display_handle;
	adxl345_info   * adxl345_handle;
} peripherals;

typedef struct {
	peripherals periph;
	game_state  state;
	sprite    * paddle;
	ball        ball;
	brick       bricks[168];
	sprite    * walls[3];
	alt_8       controller;
	alt_8       speed;
	alt_8       lives;
	alt_8       rbricks;
	alt_32      score;
	queue     * events_queue;
} game_struct;


void   breakout_init(game_struct * g, char * level_filename, alt_8 controller);
void   breakout_init_textures(game_struct * game);
alt_u8 breakout_collision(sprite *s1, sprite *s2);

#endif /* BREAKOUT_H_ */
