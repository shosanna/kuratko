#ifndef PLAYER_H
#define PLAYER_H

#include <ncurses.h>
#include "utils.h"

class Map;

constexpr char EMPTY = '.';
constexpr char PLAYER = '@';
constexpr char ENEMY = 'x';

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Player {
 public:
  size_t x = 0;
  size_t y = 0;
  size_t M;
  size_t N;

  Player(size_t x, size_t y, size_t M, size_t N) : x(x), y(y), M(M), N(N) {}

  void move(Map& map, Direction dir);
};

#endif /* PLAYER_H */
