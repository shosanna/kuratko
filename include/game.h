#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include "player.h"
#include "log.h"
#include "map.h"

void game_init_colors();
void game_loop(Log& log, Player& kuratko, Player& prasatko, WINDOW* win,
               Map& map);

#endif /* GAME_H */
