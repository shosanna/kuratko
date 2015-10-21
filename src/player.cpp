#include "player.h"
#include "core/map.h"

using namespace kuratko;

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

  switch (dir) {
    case Direction::UP:
      if (y > 0) {
        --y;
      } else {
        hlad -= 1;
        map.log << "Kuratko utika smerem k rybnicku!";
        map.log << "Z toho mu vyhladlo :(";
      }

      break;
    case Direction::DOWN:
      if (y < M - 1) {
        ++y;
      } else {
        hlad -= 1;
        map.log << "Kuratko se toula k jezevcum";
        map.log << "Z toho mu vyhladlo :(";
      }

      break;
    case Direction::LEFT:
      if (x > 0) {
        --x;
      } else {
        hlad -= 1;
        map.log << "Kuratko miri do skalnateho lesa";
        map.log << "Z toho mu vyhladlo :(";
      }

      break;
    case Direction::RIGHT:
      if (x < N - 1) {
        ++x;
      } else {
        hlad -= 1;
        map.log << "Kuratko jde smerem k lvickovi Eliasovi";
        map.log << "Z toho mu vyhladlo :(";
      }

      break;
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
  return stesti;;
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
  if(map(x,y) == KLACIK) {
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
