#include <ncurses.h>
#include <ostream>
#include "log.h"

void Log::append_line(std::string s) {
  queue.push(s);
}

Log& Log::operator<<(std::string s) {
  append_line(s);
  return *this;
}

void Log::flush() {
  while (!queue.empty()) {
    auto s = queue.front();
    queue.pop();

    std::string msg = s + "\n";
    waddstr(w, msg.c_str());

    int x, y;
    getyx(w.w, y, x);
    wmove(w, y, x + 1);
    w.box();
    w.refresh();
  }
}
