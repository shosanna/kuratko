#include "map.h"
#include <string>

void Map::reset() {
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      // auto x = data.size();
      (*this)(i, j) = EMPTY;
    }
  }
}

void Map::print(Player& kuratko) {
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

      mvwaddch(win, i+1, j+1, curr);
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

  log.append_line(hladZprava + hladStatus);
  log.append_line(get_error());

  win.refresh();

}
