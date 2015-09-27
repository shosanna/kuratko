#include "status.h"

void Status::print() {
  wmove(win, 1, 0);

  for (auto hladik : hladiky) {
    int x,y;
    getyx(win.w, y, x);
    wmove(win, y, x+1);
    wprintw(win, "%s: %d\n", hladik.first.c_str(), hladik.second);
  }

  win.refresh();
}
