#include <ncurses.h>
#include <ostream>
#include <mutex>
#include "core/log.h"

using namespace kuratko::core;

void kuratko::core::Log::append_line(std::string s) {
  std::lock_guard<std::mutex> guard{m};

  queue.push(s);
}

Log& kuratko::core::Log::operator<<(std::string s) {
  append_line(s);
  return *this;
}

void kuratko::core::Log::flush() {
  std::lock_guard<std::mutex> guard{m};


  while (!queue.empty()) {
    auto s = queue.front();
    queue.pop();

    h_(s);
  }
}
