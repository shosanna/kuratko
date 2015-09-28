#include "player.h"
#include "utils.h"
#include "map.h"

using namespace kuratko;

void toula(Player&, std::string) {
  // TODO
  // if (p.typ == KURATKO) {
  //   set_error(s);
  // }
}

void kuratko::Player::move(Map& map, int dx, int dy) {
  std::lock_guard<std::mutex> guard{mtx};

  map(x, y) = EMPTY;

  x += dx;
  y += dy;

  kolac_check(map);

  map(x, y) = typ;
}

void kuratko::Player::move(Map& map, Direction dir) {
  std::lock_guard<std::mutex> guard{mtx};

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
      if (y < M - 1) {
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
      if (x < N - 1) {
        clear_error();
        ++x;
      } else
        toula(*this, "Kuratko jde ven z lesa:(");

      break;
  }

  kolac_check(map);

  map(x, y) = typ;
}

void kuratko::Player::napapat() {
  hlad += 1;

  if (typ == KURATKO) {
    status.hladiky["Kuratko"] = hlad;
  } else if (typ == PRASATKO) {
    status.hladiky["Prasatko"] = hlad;
  }

  // TODO - detailni status kuratka
  // if (hladStatus == "0") {
  //   hladZprava = "Kuratko ma hlad!: ";
  // } else if (hladStatus == "3") {
  //   hladZprava = "Kuratko je precpano: ";
  // } else {
  //   hladZprava = "Kuratko je napapano: ";
  // }
}

int kuratko::Player::zjistiHlad() {
  return hlad;
}

void kuratko::Player::move_to_target(Map& map) {
  if (map(target.first, target.second) != KOLAC) {
    map.log << "Prasatko: \"Nekdo mi spapal kolac, musim najit novy\" :(";
    has_target = false;
    return;
  }

  if (x == target.first && y == target.second) {
    has_target = false;
  } else if (x == target.first) {
    int dy = target.second - y;

    move(map, 0, dy / abs(dy));
  } else {
    int dx = target.first - x;

    move(map, dx / abs(dx), 0);
  }
}

void kuratko::Player::kolac_check(Map& map) {
  if (map(x, y) == KOLAC) {
    napapat();
    has_target = false;

    if (typ == KURATKO) {
      map.log.append_line("Kuratko spapalo boruvkovy kolac!");
    } else {
      map.log.append_line("Prasatko spapalo boruvkovy kolac!");
    }
  }

  if (map(x, y) == PRASATKO) {
    if (typ == KURATKO) {
      map.log.append_line("Kuratko se potkalo s Prasatkem :)");
    }
  }
}
