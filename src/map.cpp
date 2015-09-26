#include "map.h"
#include <string>

void Map::reset() {
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      (*this)(i, j) = EMPTY;
    }
  }
}

void Map::print(WINDOW* win, Player& kuratko) {
  wmove(win, 0, 0);

  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      chtype curr = (*this)(i, j);

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

      mvwaddch(win, j, i, curr);
    }
  }

  std::string hladStatus = std::to_string(kuratko.zjistiHlad());
  std::string hladZprava;

  if (hladStatus == "0") {
    hladZprava = "Kuratko ma hlad!: ";
  } else if (hladStatus == "3") {
    hladZprava = "Kuratko je precpano: ";
  } else {
    hladZprava = "Kuratko je napapano: ";
  }

  for (int i = 0; i < hladZprava.size(); i++) {
    mvwaddch(win, m + 1, i, hladZprava[i]);
  }

  for (int i = 0; i < hladStatus.size(); i++) {
    mvwaddch(win, m + 1, hladZprava.size() + 1, hladStatus[i]);
  }

  std::string s = get_error();
  for (size_t i = 0; i < s.size(); i++) {
    mvwaddch(win, m + 2, i, s[i]);
  }
}
