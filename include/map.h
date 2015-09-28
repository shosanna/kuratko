#ifndef MAP_H
#define MAP_H

#include <mutex>
#include <cassert>
#include <vector>
#include <string>
#include <stdlib.h>
#include "player.h"
#include "core/log.h"
#include "status.h"

class Map {
 public:
  using Point = char;

  kuratko::gui::Window& win;
  kuratko::core::Log& log;
  Status& status;
  size_t m;
  size_t n;
  std::vector<Point> data;
  std::mutex mtx;

  Map(kuratko::gui::Window& win, kuratko::core::Log& log, Status& status, size_t m,
        size_t n)
      : win(win), log{log}, status(status), m(m), n(n), data(m * n) {
  }

  void reset();
  void print();

  Point& operator()(size_t x, size_t y) {
    std::lock_guard<std::mutex> lock(mtx);
    return data.at(n * y + x);
  }

  void pathfind(Player&);
  bool is_valid(size_t x, size_t y);
  void random_kolac();

 private:
};

#endif /* MAP_H */
