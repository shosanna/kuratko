#include "gui/log_window.h"

void kuratko::gui::f(LogWindow& win, std::string s) {
  std::string msg = s + "\n";
  waddstr(win.w, msg.c_str());

  int x, y;
  getyx(win.w, y, x);
  wmove(win.w, y, x + 1);

  win.refresh();
}

void kuratko::gui::LogWindow::refresh() {
  box();
  Window::refresh();
}
