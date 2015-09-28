#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include "core/log.h"
#include "core/input_manager.h"
#include "map.h"
#include "player.h"

void game_init_colors();
void game_loop(kuratko::core::InputManager& manager, WINDOW* win, kuratko::Map& map);

#endif /* GAME_H */
