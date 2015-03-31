#ifndef BREAKOUT_H_
#define BREAKOUT_H_

#include <includes.h>
#include <system.h>
#include "mtc.h"
#include "pic32.h"
#include "display.h"
#include "adxl345.h"

#define IMG_BALL         0
#define TEXTURE_WALL     400
#define TEXTURE_PADDLE   450
#define TEXTURE_BRICK0   550
#define TEXTURE_BRICK1   600
#define TEXTURE_BRICK2   650
#define TEXTURE_BRICK3   700


#define BALL_WIDTH       20
#define BALL_HEIGHT      20
#define NBR_BRICKS       168
#define SCORE_UNIT		 20
#define EVENT_QUEUE_SIZE 16

typedef enum {
	ADD_LIFE = 0,
	REMOVE_LIFE = 1,
	SWITCH_PADDLE_SIZE = 2,
	ADD_BALL = 3,
	SPEED_DOWN = 4,
	SPEED_UP = 5
} game_event;

typedef enum {
	PAUSED,
	NOT_MOVING,
	BALL_MOVING,
	NOGAME
} game_state;

typedef struct {
	alt_16 x;
	alt_16 y;
} vector;

typedef struct {
	sprite * s;
	vector   v;
	alt_u8   enabled;
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
	ball        balls[2];
	brick       bricks[168];
	sprite    * walls[3];
	alt_8       speed;
	alt_8       lives;
	alt_32      score;
	queue     * events_queue;
} game_struct;


void breakout_init(game_struct * g, char * level_filename);
void breakout_create_textures();

#endif /* BREAKOUT_H_ */
