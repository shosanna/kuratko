#include "gui/status_window.h"

using namespace kuratko::gui;

void kuratko::gui::StatusWindow::refresh() {
  wmove(w, 1, 1);

  wattron(w, A_UNDERLINE);
  waddstr(w, "Hladiky:\n");
  wattroff(w, A_UNDERLINE);

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

  int x,y;
  getyx(w, y, x);
  wmove(w, y, x+1);
  wattron(w, A_UNDERLINE);
  waddstr(w, "Stestiky:\n");
  wattroff(w, A_UNDERLINE);

  for (auto stesti : stestiky) {
    int x,y;
    getyx(w, y, x);
    wmove(w, y, x+1);

    wprintw(w, "%s: %d\n", stesti.first.c_str(), stesti.second);
  }

  mvwprintw(w, 0, 1, "Status");
  ready_cursor();

  Window::box();
  Window::refresh();
}
