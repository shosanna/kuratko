#include <string>
#include <regex>
#include <queue>
#include <utility>
#include <unordered_map>
#include "map.h"
#include <cmath>
#include <fstream>

using namespace std;

void Map::reset() {
  for (size_t y = 0; y < m; y++) {
    for (size_t x = 0; x < n; x++) {
      // auto x = data.size();
      (*this)(x, y) = EMPTY;
    }
  }
}

void Map::print() {
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
      }

      mvwaddch(win, y + 1, x + 1, curr);
    }
  }

  std::string err = get_error();
  if (err.size()) {
    log.append_line(err);
  }

  status.print();
  win.refresh();
}

using coord = std::pair<size_t, size_t>;

struct Pair_hash {
  size_t operator()(const coord& c) const {
    return c.first + c.second;
  }
};

void Map::pathfind(Player& p) {
  if (p.has_target) {
    log.append_line("moving to target");
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

          log << "set target to " << std::to_string(next.first) << " " << std::to_string(next.second);
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

bool Map::is_valid(size_t x, size_t y) {
  return x < n && y < m;
}
