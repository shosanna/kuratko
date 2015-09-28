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

static void tapkat(Player& prasatko, Map& map) {
  while (1) {
    this_thread::sleep_for(chrono::milliseconds(800));
    map.pathfind(prasatko);
  }
}

static void kolace(Map& map) {
  while (1) {
    this_thread::sleep_for(chrono::seconds(5));
    map.random_kolac();
  }
}

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

void game_loop(Player& kuratko, Player& prasatko, WINDOW* win, Map& map) {
  thread t(tapkat, ref(prasatko), ref(map));
  thread t2(kolace, ref(map));

  core::InputManager manager;

  auto f = [&kuratko, &map](int c) {
    switch (c) {
      case 'a':
      case KEY_LEFT:
      case 'h':
        kuratko.move(map, Direction::LEFT);
        break;
      case 'w':
      case KEY_UP:
      case 'k':
        kuratko.move(map, Direction::UP);
        break;
      case 's':
      case KEY_DOWN:
      case 'j':
        kuratko.move(map, Direction::DOWN);
        break;
      case 'd':
      case KEY_RIGHT:
      case 'l':
        kuratko.move(map, Direction::RIGHT);
        break;
      case 'q':
        exit(0);
    }
  };

  manager.add(f);

  while (1) {
    update(manager);
    render(win, map);
  }

  t.join();
  t2.join();
}

void game_init_colors() {
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_YELLOW);
  init_pair(3, COLOR_BLACK, COLOR_RED);
}
