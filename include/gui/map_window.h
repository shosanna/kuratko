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

  core::Log& log;
  gui::StatusWindow& status;

  core::Map& map;

  MapWindow(int h, int w, int y, int x, core::Log& log,
            gui::StatusWindow& status, core::Map& map)
      : Window(h, w, y, x), log(log), status(status), map(map) {
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
