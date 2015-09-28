#include <string>
#include <regex>
#include <queue>
#include <utility>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include <thread>

#include "map.h"

using namespace std;

void kuratko::Map::reset() {
  for (size_t y = 0; y < m; y++) {
    for (size_t x = 0; x < n; x++) {
      // auto x = data.size();
      (*this)(x, y) = EMPTY;
    }
  }
}

void kuratko::Map::print() {
  for (size_t y = 0; y < m; y++) {
    for (size_t x = 0; x < n; x++) {
      chtype curr = (*this)(x, y);

      switch (curr) {
        case KURATKO:
          curr = curr | COLOR_PAIR(2);
          break;

        case EMPTY:
          break;

        case KOLAC:
          curr = curr | COLOR_PAIR(1);
          break;

        case PRASATKO:
          curr = curr | COLOR_PAIR(3);
          break;

        case KLACIK:
          curr = curr | COLOR_PAIR(4);
          break;
      }

      mvwaddch(win, y + 1, x + 1, curr);
    }
  }

  // TODO - check out if this is still correct
  // status.print();
  status.refresh();

  win.refresh();
}

using coord = std::pair<size_t, size_t>;

struct Pair_hash {
  size_t operator()(const coord& c) const {
    return c.first + c.second;
  }
};

void kuratko::Map::pathfind(Player& p) {
  if (p.has_target) {
    p.move_to_target(*this);
    return;
  }

  enum { WHITE = 0, GRAY = 1, BLACK = 2 };

  queue<coord> queue;
  unordered_map<coord, int, Pair_hash> colors;

  coord curr = {p.x, p.y};
  queue.push(curr);
  colors[curr] = GRAY;

  vector<pair<int, int>> diffs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  bool found = false;
  pair<int, int> found_diff;

  while (!queue.empty()) {
    curr = queue.front();
    queue.pop();

    if (colors[curr] == BLACK) continue;

    for (auto diff : diffs) {
      coord next = {curr.first + diff.first, curr.second + diff.second};

      // Invalid coords are simply ignored.
      if (is_valid(next.first, next.second)) {
        if ((*this)(next.first, next.second) == KOLAC) {
          p.target = next;
          p.has_target = true;
          found = true;
          goto found_kolac;
        } else {
          queue.push(next);
          colors[next] = GRAY;
          colors[curr] = BLACK;
        }
      }
    }
  }

found_kolac:
  if (found) {
    p.move_to_target(*this);
  } else {
    exit(1);
  }
}

bool kuratko::Map::is_valid(size_t x, size_t y) {
  return x < n && y < m;
}

void kuratko::Map::random_item(char item) {
  // TODO - race condition? see thread sanitizer
  std::random_device rd;
  std::uniform_int_distribution<size_t> x_dis(0, n - 1);
  std::uniform_int_distribution<size_t> y_dis(0, m - 1);
  std::mt19937 gen(rd());
  (*this)(x_dis(gen), y_dis(gen)) = item;
}
