#ifndef LOG_H
#define LOG_H

#include <cstdlib>
#include <string>
#include <ncurses.h>
#include <queue>
#include "window.h"

class Log {
  Window& w;
  std::string data;
  std::queue<std::string> queue;

 public:
  Log(Window& w) : w(w) {}

  void append_line(std::string s);
  Log& operator<<(std::string);
  void flush();

};

#endif /* LOG_H */
