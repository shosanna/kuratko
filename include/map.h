#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <stdlib.h>
#include "player.h"
#include "log.h"

class Map {
 public:
  using Point = char;

  Window& win;
  Log log;
  size_t m;
  size_t n;
  std::vector<Point> data;

  Map(Window& win, Log& log, size_t m, size_t n)
      : win{win}, log{log}, m{m}, n{n}, data(m * n) {
  }

  void reset();
  void print(Player& player);

  Point& operator()(size_t i, size_t j) {
    return data.at(n * i + j);
  }

 private:
};

#endif /* MAP_H */
