#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <stdlib.h>
#include "player.h"

class Map {
  public:
  using Point = char;

  Map(size_t m, size_t n) : m(m), n(n), data(m * n) {}
  Point& operator()(size_t i, size_t j) { return data.at(n * i + j); }

  void reset();
  void print(WINDOW* win);

  const size_t m;
  const size_t n;

 private:
  std::vector<Point> data;
};

// void map_clear() { cout << static_cast<char>(27) << "[2J"; }
// void map_switch_color(const char* color) { cout << color; }

#endif /* MAP_H */
