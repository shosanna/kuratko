#ifndef MAP_H
#define MAP_H

#include <cassert>
#include <vector>
#include <string>
#include <stdlib.h>
#include "player.h"
#include "log.h"
#include "status.h"

class Map {
 public:
  using Point = char;

  Window& win;
  Log& log;
  Status& status;
  size_t m;
  size_t n;
  std::vector<Point> data;

  Map(Window& win, Log& log, Status& status, size_t m, size_t n)
      : win(win), log{log}, status(status), m(m), n(n), data(m * n) {
  }

  void reset();
  void print(Player& player);

  Point& operator()(size_t x, size_t y) {
    int index = n * y + x;
    assert(index < m*n);
    // return data.at(n * y + x);
    return data[index];
  }

 private:
};

#endif /* MAP_H */
