#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

namespace kuratko {
namespace gui {

class Window {
 public:
  WINDOW* w;

  Window(size_t w, size_t h, size_t x = 0, size_t y = 0)
      : w{newwin(w, h, x, y)} {
  }

  virtual ~Window() {
    delwin(w);
  }

  void box() {
    ::box(w, 0, 0);
    refresh();
  }

  void refresh() {
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
