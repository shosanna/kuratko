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

  size_t m;
  size_t n;

  core::Map map;
  MapWindow(int h, int w, int y, int x, kuratko::core::Log& log,
            gui::StatusWindow& status, size_t m, size_t n)
      : Window(h, w, y, x), log(log), status(status), m(m), n(n), map(m, n) {

    map.reset();
    mvwprintw(*this, 0, 1, "Zviratkovy les");
    box();
    ready_cursor();
    refresh();
  }

  void print();

  Point& operator()(size_t x, size_t y) {
    return map(x, y);
  }

  void pathfind(Player&);
  bool is_valid(size_t x, size_t y);
  void random_item(char item);

 private:
};
}

#endif /* MAP_WINDOW_H */
