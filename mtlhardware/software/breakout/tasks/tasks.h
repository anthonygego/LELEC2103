#ifndef TASKS_H_
#define TASKS_H_

#include "breakout.h"

void status_task(void* pdata);
void rpc_task(void* pdata);
void game_task(void* pdata);
void console_task(void* pdata);

void rpc_game_start(game_struct * game, alt_u8 level);
void rpc_game_event(game_struct * game, game_event ge);

#endif /* TASKS_H_ */
