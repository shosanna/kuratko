#include <thread>
#include <chrono>
#include <ncurses.h>
#include <vector>
#include <random>
#include "log.h"
#include "game.h"
#include "core/input_manager.h"

using namespace kuratko;
using namespace std;

static void update(core::InputManager& manager) {
  int c = getch();
  if (c == ERR) return;

  manager.handle(c);
}

static void render(WINDOW* win, Map& map) {
  map.log.flush();
  map.print();
  wmove(win, 50, 50);
  wrefresh(win);
}

void game_loop(core::InputManager& manager, WINDOW* win, Map& map) {

  while (1) {
    update(manager);
    render(win, map);
  }
}

void game_init_colors() {
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_YELLOW);
  init_pair(3, COLOR_BLACK, COLOR_RED);
}
