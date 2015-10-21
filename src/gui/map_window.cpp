#include <string>
#include <regex>
#include <queue>
#include <utility>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include <thread>

#include "gui/map_window.h"

using namespace std;

void kuratko::MapWindow::print() {
  for (size_t y = 0; y < map.m; y++) {
    for (size_t x = 0; x < map.n; x++) {
      chtype curr = map(x, y);

      switch (curr) {
        case KURATKO:
          curr = curr | COLOR_PAIR(2);
          break;

        case EMPTY:
          break;

        case KOLAC:
          curr = curr | COLOR_PAIR(1);
          break;

        case PRASATKO:
          curr = curr | COLOR_PAIR(3);
          break;

        case KLACIK:
          curr = curr | COLOR_PAIR(4);
          break;
      }

      mvwaddch(*this, y + 1, x + 1, curr);
    }
  }

  // TODO - check out if this is still correct
  // status.print();
  status.refresh();

  refresh();
}

