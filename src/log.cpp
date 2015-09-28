#include <ncurses.h>
#include <ostream>
#include <mutex>
#include "log.h"

void Log::append_line(std::string s) {
  std::lock_guard<std::mutex> guard{m};

  queue.push(s);
}

Log& Log::operator<<(std::string s) {
  append_line(s);
  return *this;
}

void Log::flush() {
  std::lock_guard<std::mutex> guard{m};


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
