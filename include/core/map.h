#include <vector>
#include <mutex>
#include "core/log.h"
#include "player.h"

namespace kuratko {
namespace core {
class Map {
 public:
  using Point = char;

  Log& log;
  std::mutex mtx;
  size_t m;
  size_t n;
  std::vector<Point> data;

  Map(Log& log, size_t m, size_t n) : log(log), m(m), n(n), data(m * n) {
    this->reset();
  }

  Point& operator()(size_t x, size_t y);
  void reset();

  void pathfind(Player&);
  bool is_valid(size_t x, size_t y);
  void random_item(char item);
};
}
}
