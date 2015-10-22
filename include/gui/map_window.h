#ifndef MAP_WINDOW_H
#define MAP_WINDOW_H

#include <mutex>
#include <cassert>
#include <vector>
#include <string>
#include <stdlib.h>

#include "player.h"

#include "core/map.h"
#include "core/log.h"

#include "gui/status_window.h"
#include "gui/window.h"

namespace kuratko {
class MapWindow : public gui::Window {
 public:
  using Point = char;

  // These are just for the window size (not the whole map)
  size_t window_m;
  size_t window_n;
  // offset within the window
  size_t offset_x;
  size_t offset_y;
  core::Log& log;
  gui::StatusWindow& status;

  core::Map& map;

  MapWindow(size_t window_m, size_t window_n, int h, int w, int y, int x,
            core::Log& log, gui::StatusWindow& status, core::Map& map)
      : Window(h, w, y, x),
        window_m(window_m),
        window_n(window_n),
        offset_x(0),
        offset_y(0),
        log(log),
        status(status),
        map(map) {

    mvwprintw(*this, 0, 1, "Zviratkovy les");
    box();
    ready_cursor();
    refresh();
  }

  void print();

 private:
};
}

#endif /* MAP_WINDOW_H */
