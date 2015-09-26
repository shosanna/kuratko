#include "player.h"
#include "utils.h"
#include "map.h"

void Player::move(Map& map, Direction dir) {
  map(x, y) = EMPTY;

  switch (dir) {
    case Direction::UP:
      if (y > 0)
        --y;
      else
        set_error("chyba y");

      break;
    case Direction::DOWN:
      if (y < M-1)
        ++y;
      else
        set_error("chyba y");

      break;
    case Direction::LEFT:
      if (x > 0)
        --x;
      else
        set_error("chyba x");

      break;
    case Direction::RIGHT:
      if (x < N-1)
        ++x;
      else
        set_error("chyba x");

      break;
  }

  map(x, y) = PLAYER;
}
