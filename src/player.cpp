#include <algorithm>
#include <sstream>
#include "player.h"
#include "core/map.h"

using namespace std;
using namespace kuratko;

struct invalid_direction {};

std::pair<int, int> dir_diff(Direction dir) {
  switch (dir) {
    case Direction::LEFT:
      return {-1, 0};
    case Direction::RIGHT:
      return {1, 0};
    case Direction::UP:
      return {0, -1};
    case Direction::DOWN:
      return {0, 1};
    default:
      throw invalid_direction{};
  }
}

Direction from_action(core::InputAction action) {
  switch (action) {
    case core::InputAction::Left:
      return Direction::LEFT;
    case core::InputAction::Right:
      return Direction::RIGHT;
    case core::InputAction::Up:
      return Direction::UP;
    case core::InputAction::Down:
      return Direction::DOWN;
    default:
      throw core::invalid_input_action{};
  }
}

void kuratko::Player::move(core::Map& map, int dx, int dy) {
  std::lock_guard<std::mutex> guard{mtx};
  uprav_statusy();

  map(x, y) = EMPTY;

  x += dx;
  y += dy;

  kolac_check(map);
  klacik_check(map);

  map(x, y) = typ;
}

void kuratko::Player::move(core::Map& map, Direction dir) {
  std::lock_guard<std::mutex> guard{mtx};

  uprav_statusy();
  map(x, y) = EMPTY;

  auto diff = dir_diff(dir);

  if (map.is_valid(x + diff.first, y + diff.second)) {
    x = x + diff.first;
    y = y + diff.second;
  } else {
    switch (dir) {
      case Direction::UP:
        map.log << "Kuratko utika smerem k rybnicku!";
        break;
      case Direction::DOWN:
        map.log << "Kuratko se toula k jezevcum";
        break;
      case Direction::LEFT:
        map.log << "Kuratko miri do skalnateho lesa";
        break;
      case Direction::RIGHT:
        map.log << "Kuratko jde smerem k lvickovi Eliasovi";
        break;
    }

    map.log << "Z toho mu vyhladlo :(";
    --hlad;
  }

  kolac_check(map);
  klacik_check(map);

  map(x, y) = typ;
}

void kuratko::Player::napapat() {
  hlad += 1;

  uprav_statusy();

  // TODO - detailni status kuratka
  // if (hladStatus == "0") {
  //   hladZprava = "Kuratko ma hlad!: ";
  // } else if (hladStatus == "3") {
  //   hladZprava = "Kuratko je precpano: ";
  // } else {
  //   hladZprava = "Kuratko je napapano: ";
  // }
}

int kuratko::Player::zjisti_hlad() {
  return hlad;
}

int kuratko::Player::zjisti_stesti() {
  return stesti;
}

void kuratko::Player::move_to_target(core::Map& map) {
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

void kuratko::Player::hrat_s_klacikem() {
  stesti += 1;
  hlad -= 1;

  uprav_statusy();
}

void kuratko::Player::klacik_check(core::Map& map) {
  if (map(x, y) == KLACIK) {
    hrat_s_klacikem();

    if (typ == KURATKO) {
      map.log << "Kuratko si hraje s klacikem!";
    } else if (typ == PRASATKO) {
      map.log << "Prasatko stavi klacikovy domecek.";
    }
  }
}

void kuratko::Player::kolac_check(core::Map& map) {
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

void kuratko::Player::uprav_statusy() {
  if (typ == KURATKO) {
    status.stestiky["Kuratko"] = stesti;
    status.hladiky["Kuratko"] = hlad;
  } else if (typ == PRASATKO) {
    status.stestiky["Prasatko"] = stesti;
    status.hladiky["Prasatko"] = hlad;
  }
}
