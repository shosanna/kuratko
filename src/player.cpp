#include "player.h"
#include "utils.h"
#include "map.h"

void toula(Player& p, std::string s) {
  // TODO
  // if (p.typ == KURATKO) {
  //   set_error(s);
  // }
}

void Player::move(Map& map, Direction dir) {
  map(x, y) = EMPTY;

  switch (dir) {
    case Direction::UP:
      if (y > 0) {
        clear_error();
        --y;
      } else
        toula(*this, "Kuratko se toula pryc!");

      break;
    case Direction::DOWN:
      if (y < M-1) {
        clear_error();
        ++y;
      } else
        toula(*this, "Kuratko se toula pryc!");

      break;
    case Direction::LEFT:
      if (x > 0) {
        clear_error();
        --x;
      } else
        toula(*this, "Kuratko jde ven z lesa:(");

      break;
    case Direction::RIGHT:
      if (x < N-1) {
        clear_error();
        ++x;
      } else
        toula(*this, "Kuratko jde ven z lesa:(");

      break;
  }

  if (map(x,y) == KOLAC) {
    napapat();

    if (typ == KURATKO) {
      set_error("Kuratko spapalo boruvkovy kolac!");
    } else {
      set_error("Prasatko spapalo boruvkovy kolac!");
    }
  }

  map(x, y) = typ;
}

void Player::napapat() {
  hlad += 1;
}

int Player::zjistiHlad() {
  return hlad;
}
