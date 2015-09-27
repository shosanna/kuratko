#include <ncurses.h>
#include <ostream>
#include "log.h"

void Log::append_line(std::string s) {
  std::string msg = s + "\n";
  waddstr(w, msg.c_str());

  int x,y;
  getyx(w.w, y, x);
  wmove(w, y, x+1);
  w.box();
  w.refresh();
}

Log& Log::operator<<(std::string s) { append_line(s); return *this; }
