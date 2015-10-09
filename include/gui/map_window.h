#ifndef MAP_H
#define MAP_H

#include <mutex>
#include <cassert>
#include <vector>
#include <string>
#include <stdlib.h>
#include "player.h"
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
  std::vector<Point> data;
  std::mutex mtx;

  MapWindow(int h, int w, int y, int x, kuratko::core::Log& log, gui::StatusWindow& status, size_t m,
        size_t n)
      : Window(h,w,y,x), log(log), status(status), m(m), n(n), data(m * n) {

        mvwprintw(*this, 0, 1, "Zviratkovy les");
        box();
        ready_cursor();
        refresh();
  }

  void reset();
  void print();

  Point& operator()(size_t x, size_t y) {
    std::lock_guard<std::mutex> lock(mtx);
    return data.at(n * y + x);
  }

  void pathfind(Player&);
  bool is_valid(size_t x, size_t y);
  void random_item(char item);

 private:
};
}


#endif /* MAP_H */
