#include "status.h"

void Status::print() {
  wmove(win, 1, 1);

  waddstr(win, "Hladiky:\n");

  for (auto hladik : hladiky) {
    int x,y;
    getyx(win.w, y, x);
    wmove(win, y, x+1);

    if (hladik.second > 3) {
      start_color();
      wattron(win, COLOR_PAIR(3));
      wprintw(win, "%s: %d\n", hladik.first.c_str(), hladik.second);
      wattroff(win, COLOR_PAIR(3));
    } else {
      wprintw(win, "%s: %d\n", hladik.first.c_str(), hladik.second);
    }
  }

  win.box();
  win.refresh();
}
