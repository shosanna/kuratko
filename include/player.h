#ifndef PLAYER_H
#define PLAYER_H

#include <utility>
#include <ncurses.h>
#include "utils.h"
#include "status.h"

class Map;

constexpr char EMPTY = '.';
constexpr char KURATKO = '^';
constexpr char KOLAC = 'O';
constexpr char PRASATKO = '@';

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Player {
 public:
  char typ;
  Status& status;
  size_t x = 0;
  size_t y = 0;
  size_t M;
  size_t N;
  bool has_target = false;
  std::pair<size_t, size_t> target;


  Player(char typ, Status& s, size_t x, size_t y, size_t M, size_t N)
      : typ(typ), status(s), x(x), y(y), M(M), N(N) {}

  void move(Map& map, int dx, int dy);
  void move(Map& map, Direction dir);
  void napapat();
  int zjistiHlad();

  void move_to_target(Map& map);
  void kolac_check(Map& map);

 private:
  int hlad = 0;
};

#endif /* PLAYER_H */
