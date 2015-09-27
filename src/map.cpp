#include "map.h"
#include <string>
#include <regex>

void Map::reset() {
  for (size_t y = 0; y < m; y++) {
    for (size_t x = 0; x < n; x++) {
      // auto x = data.size();
      (*this)(x, y) = EMPTY;
    }
  }
}

void Map::print() {
  for (size_t y = 0; y < m; y++) {
    for (size_t x = 0; x < n; x++) {
      chtype curr = (*this)(x, y);

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
      }

      mvwaddch(win, y+1, x+1, curr);
    }
  }

  std::string err = get_error();
  if (err.size()) {
    log.append_line(err);
  }

  status.print();
  win.refresh();

}
