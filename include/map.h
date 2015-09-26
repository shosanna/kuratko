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

  Map(Log& log, size_t m, size_t n) : log(log), m(m), n(n), data(m * n) {}
  Point& operator()(size_t i, size_t j) { return data.at(n * i + j); }

  void reset();
  void print(WINDOW* win, Player& player);

  Log log;
  const size_t m;
  const size_t n;

 private:
  std::vector<Point> data;
};

#endif /* MAP_H */
