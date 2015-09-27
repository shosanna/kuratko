#ifndef LOG_H
#define LOG_H

#include <cstdlib>
#include <string>
#include <ncurses.h>
#include "window.h"

class Log {
  Window& w;
  std::string data;

 public:
  Log(Window& w) : w(w) {}

  void append_line(std::string s);
  Log& operator<<(std::string);

};

#endif /* LOG_H */
