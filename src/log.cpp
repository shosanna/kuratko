#include <ncurses.h>
#include <ostream>
#include "log.h"

void Log::append_line(std::string s) {
  waddstr(w, (s + "\n").c_str());
  int x,y;
  getyx(w.w, y, x);
  wmove(w, y, x+1);
  w.refresh();
}
