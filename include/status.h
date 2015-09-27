#ifndef STATUS_H
#define STATUS_H

#include <map>
#include <string>
#include "window.h"

class Status {
 public:
  Window& win;
  std::map<std::string, int> hladiky;

  Status(Window& win) : win(win) {
  }

  void print();
};

#endif /* STATUS_H */
