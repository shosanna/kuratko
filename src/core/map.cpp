#include <algorithm>
#include <mutex>
#include "core/map.h"
#include "player.h"

using namespace std;
using namespace kuratko::core;

Map::Point& kuratko::core::Map::operator()(size_t x, size_t y) {
  lock_guard<mutex> lock{mtx};
  return data.at(n * y + x);
}

void kuratko::core::Map::reset() {
  std::fill(data.begin(), data.end(), EMPTY);
}
