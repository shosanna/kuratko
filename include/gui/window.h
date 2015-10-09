#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

namespace kuratko {
namespace gui {

class Window {
 public:
  WINDOW* w;

  Window(size_t h, size_t w, size_t y = 0, size_t x = 0)
      : w{newwin(h, w, y, x)} {
  }

  virtual ~Window() {
    delwin(w);
  }

  void box() {
    ::box(w, 0, 0);
  }

  virtual void refresh() {
    ::wrefresh(w);
  }

  operator WINDOW*() {
    return w;
  }

  void ready_cursor() {
    ::wmove(*this, 1, 1);
  }
};
}
}

#endif /* WINDOW_H */
