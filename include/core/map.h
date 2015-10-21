#include <vector>
#include <mutex>

namespace kuratko {
  namespace core {
    class Map {
      public:
        using Point = char;

        std::mutex mtx;
        size_t m;
        size_t n;
        std::vector<Point> data;

        Map(size_t m, size_t n) : m(m), n(n), data(m * n) {
        }

        Point& operator()(size_t x, size_t y);
    };
  }
}
