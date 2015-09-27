#include <thread>
#include <chrono>
#include <ncurses.h>
#include <vector>
#include <random>
#include "log.h"
#include "game.h"

using namespace std;

void tapkat(Player& prasatko, Map& map) {
  while(1) {
    this_thread::sleep_for(chrono::milliseconds(800));

    map.log << "pathfinding";
    map.pathfind(prasatko);
  }
}

void kolace(Map& map) {
  while (1) {
    this_thread::sleep_for(chrono::seconds(5));
    map.random_kolac();
  }
}

void game_loop(Player& kuratko, Player& prasatko, WINDOW* win, Map& map) {
  thread t(tapkat, ref(prasatko), ref(map));
  thread t2(kolace, ref(map));

  while (1) {
    map.log.flush();
    map.print();
    wmove(win, 50, 50);
    wrefresh(win);

    int c = getch();
    if (c == ERR) continue;

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
