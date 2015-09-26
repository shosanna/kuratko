#include "map.h"

void Map::reset() {
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      (*this)(i, j) = EMPTY;
    }
  }
}

void Map::print(WINDOW* win) {
  wmove(win, 0, 0);

  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      chtype curr = (*this)(i, j);

      switch (curr) {
        case PLAYER:
          curr = curr | COLOR_PAIR(2);
          break;

        case EMPTY:
          break;

        case ENEMY:
          curr = curr | COLOR_PAIR(1);
          break;
      }

      mvwaddch(win, j, i, curr);
    }
  }

  std::string s = get_error();
  for (size_t i = 0; i < s.size(); i++) {
    mvwaddch(win, m + 1, i, s[i]);
  }
}
