#ifndef LOG_WINDOW_H
#define LOG_WINDOW_H

#include <ncurses.h>
#include <string>
#include <functional>
#include "core/log.h"
#include "gui/window.h"

namespace kuratko {
namespace gui {

class LogWindow;
void f(LogWindow& win, std::string s);

class LogWindow : public Window {
 public:
  core::Log log;

  LogWindow(size_t w, size_t h, size_t x = 0, size_t y = 0)
      : Window(w, h, x, y),
        log(std::bind(f, std::ref(*this), std::placeholders::_1)) {
  }

  virtual void refresh() override;
};
}
}

#endif /* LOG_WINDOW_H */
