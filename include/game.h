#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include "player.h"
#include "log.h"
#include "map.h"
#include "core/input_manager.h"

void game_init_colors();
void game_loop(kuratko::core::InputManager& manager, WINDOW* win, Map& map);

#endif /* GAME_H */
