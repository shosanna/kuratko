#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include "player.h"
#include "map.h"

void game_init_colors();
void game_loop(Player& p, WINDOW* win, Map& map);

#endif /* GAME_H */
