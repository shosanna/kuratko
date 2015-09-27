#include <vector>
#include <random>
#include "log.h"
#include "game.h"

void game_loop(Log& log, Player& kuratko, Player& prasatko, WINDOW* win, Map& map) {
  while (1) {
    std::vector<Direction> dirs = {
      Direction::UP,
      Direction::DOWN,
      Direction::LEFT,
      Direction::RIGHT
    };

    std::random_device rd;
    std::uniform_int_distribution<size_t> dis(0, dirs.size());
    std::mt19937 gen(rd());

    prasatko.move(map, dirs[dis(gen)]);

    map.print(kuratko);
    wmove(win, 50, 50);
    wrefresh(win);

    char c = getch();

    switch (c) {
      case 'h':
        kuratko.move(map, Direction::LEFT);
        break;
      case 'k':
        kuratko.move(map, Direction::UP);
        break;
      case 'j':
        kuratko.move(map, Direction::DOWN);
        break;
      case 'l':
        kuratko.move(map, Direction::RIGHT);
        break;
      case 'q':
        exit(0);
    }
  }
}

void game_init_colors() {
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_YELLOW);
  init_pair(3, COLOR_BLACK, COLOR_RED);
}
