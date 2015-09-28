#ifndef STATUS_H
#define STATUS_H

#include <map>
#include <string>
#include "gui/window.h"

class Status {
 public:
  kuratko::gui::Window& win;
  std::map<std::string, int> hladiky;

  Status(kuratko::gui::Window& win) : win(win) {
  }

  void print();
};

#endif /* STATUS_H */
