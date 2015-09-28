#ifndef LOG_H
#define LOG_H

#include <mutex>
#include <cstdlib>
#include <string>
#include <ncurses.h>
#include <queue>
#include <functional>

#include "gui/window.h"

namespace kuratko {
namespace core {

class Log {
  using Handler = std::function<void(std::string)>;
  Handler h_;
  std::string data;
  std::queue<std::string> queue;
  std::mutex m;

 public:
  Log(Handler h) : h_(h) {
  }

  void append_line(std::string s);
  Log& operator<<(std::string);
  void flush();
};
}
}
#endif /* LOG_H */
