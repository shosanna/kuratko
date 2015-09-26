#include <ncurses.h>
#include <ostream>
#include "log.h"

void Log::append_line(std::string s) {
  data += s + "\n";
}

void Log::print(WINDOW* win) {
  wmove(win, y, x);

  for (char c : data) {
    waddch(win, c);
  }
}
