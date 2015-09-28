#include "gui/status_window.h"

using namespace kuratko::gui;

void kuratko::gui::StatusWindow::refresh() {
  wmove(w, 1, 1);

  waddstr(w, "Hladiky:\n");

  for (auto hladik : hladiky) {
    int x,y;
    getyx(w, y, x);
    wmove(w, y, x+1);

    if (hladik.second > 3) {
      start_color();
      wattron(w, COLOR_PAIR(3));
      wprintw(w, "%s: %d\n", hladik.first.c_str(), hladik.second);
      wattroff(w, COLOR_PAIR(3));
    } else {
      wprintw(w, "%s: %d\n", hladik.first.c_str(), hladik.second);
    }
  }

  Window::box();
  Window::refresh();
}
