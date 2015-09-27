#ifndef PLAYER_H
#define PLAYER_H

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

  Player(char typ, Status& s, size_t x, size_t y, size_t M, size_t N)
      : typ(typ), status(s), x(x), y(y), M(M), N(N) {}

  void move(Map& map, Direction dir);
  void napapat();
  int zjistiHlad();

 private:
  int hlad = 0;
};

#endif /* PLAYER_H */
