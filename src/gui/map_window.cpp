#include <algorithm>
#include <string>
#include <regex>
#include <queue>
#include <utility>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include <thread>

#include "gui/map_window.h"
#include "core/map.h"

using namespace std;

void kuratko::MapWindow::print() {
  int offset_x = 0;
  int offset_y = 0;

  if (kuratko) {
    offset_x = std::max<int>(0, kuratko->x - window_n / 2);
    offset_y = std::max<int>(0, kuratko->y - window_m / 2);
  }

  for (size_t y = offset_y; y < window_m; y++) {
    for (size_t x = offset_x; x < window_n; x++) {
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
