#include <mutex>
#include "core/map.h"

using namespace std;
using namespace kuratko::core;

Map::Point& kuratko::core::Map::operator()(size_t x, size_t y) {
  lock_guard<mutex> lock{mtx};
  return data.at(n * y + x);
}

