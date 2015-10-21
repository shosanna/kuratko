#ifndef PLAYER_H
#define PLAYER_H

#include <mutex>
#include <utility>
#include <ncurses.h>

#include "gui/status_window.h"

constexpr char EMPTY = '.';
constexpr char KURATKO = '^';
constexpr char KOLAC = 'O';
constexpr char PRASATKO = '@';
constexpr char KLACIK = 'x';

enum class Direction { UP, DOWN, LEFT, RIGHT };

namespace kuratko {
namespace core {
class Map;
}

class Player {
 public:
  char typ;
  gui::StatusWindow& status;
  size_t x = 0;
  size_t y = 0;
  size_t M;
  size_t N;
  bool has_target;
  std::pair<size_t, size_t> target;

  std::mutex mtx;

  Player(char typ, gui::StatusWindow& s, size_t x, size_t y, size_t M, size_t N)
      : typ(typ), status(s), x(x), y(y), M(M), N(N), has_target(false) {
    if (typ == KURATKO) {
      s.stestiky["Kuratko"] = stesti;
      s.hladiky["Kuratko"] = hlad;
    } else if (typ == PRASATKO) {
      s.stestiky["Prasatko"] = stesti;
      s.hladiky["Prasatko"] = hlad;
    }
  }

  void move(core::Map& map, int dx, int dy);
  void move(core::Map& map, Direction dir);
  void napapat();
  void hrat_s_klacikem();
  int zjisti_hlad();
  int zjisti_stesti();

  void uprav_statusy();
  void move_to_target(core::Map& map);
  void kolac_check(core::Map& map);
  void klacik_check(core::Map& map);

 private:
  int hlad = 0;
  int stesti = 0;
};
}

#endif /* PLAYER_H */
