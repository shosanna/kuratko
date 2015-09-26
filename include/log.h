#ifndef LOG_H
#define LOG_H

#include <cstdlib>
#include <string>
#include <ncurses.h>

class Log {
  size_t x, y, m, n;
  std::string data;

 public:
  Log(size_t x, size_t y, size_t m, size_t n) : x(x), y(y), m(m), n(n) {}

  void append_line(std::string s);
  void print(WINDOW* win);
};

#endif /* LOG_H */
