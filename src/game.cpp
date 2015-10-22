#include <thread>
#include <chrono>
#include <ncurses.h>
#include <vector>
#include <random>
#include <cstdlib>
#include <iostream>

#include "game.h"
#include "player.h"

#include "core/log.h"
#include "core/input_manager.h"
#include "core/map.h"

#include "gui/map_window.h"
#include "gui/log_window.h"
#include "gui/status_window.h"
#include "gui/window.h"

using namespace std;
using namespace kuratko;

static void tapkat(Player& prasatko, core::Map& map);
static void kolace(core::Map& map);

static void update(core::InputManager& manager) {
  int c = getch();
  if (c == ERR) return;

  manager.handle(c);
}

static void render(MapWindow& map) {
  map.log.flush();
  map.print();
  map.refresh();
  // wmove(map.win, 50, 50);
  // wrefresh(map.win);
}

void game_loop(core::InputManager& manager, MapWindow& map) {
  while (1) {
    update(manager);
    render(map);
  }
}

void game_init_colors() {
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_YELLOW);
  init_pair(3, COLOR_BLACK, COLOR_RED);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
}

static void cleanup_ncurses() {
  endwin();
}

void game() {
  initscr();

  std::atexit(cleanup_ncurses);

  start_color();
  init_pair(1, COLOR_RED, COLOR_BLUE);

  halfdelay(1);
  // cbreak();
  keypad(stdscr, TRUE);
  refresh();
  noecho();
  // TODO - co to je?
  // nonl();
  // intrflush(stdscr, false);

  int maxy, maxx;

  getmaxyx(stdscr, maxy, maxx);

  double xratio = 0.7;
  double yratio = 0.8;
  if (maxy > maxx / 2) {
      yratio = 0.6;
  }

  int sidebar_pos = static_cast<int>(maxx * xratio);
  int footer_pos = static_cast<int>(maxy * yratio);
  size_t M = footer_pos - 2;
  size_t N = sidebar_pos - 2;

  gui::StatusWindow sidebar(footer_pos, maxx - sidebar_pos, 0, sidebar_pos);
  sidebar.box();
  sidebar.refresh();

  gui::LogWindow footer(maxy - footer_pos, maxx, footer_pos, 0);
  footer.ready_cursor();
  footer.refresh();

  scrollok(footer, TRUE);


  game_init_colors();

  core::Map map{footer.log, M, N};
  MapWindow map_window{ footer_pos - 4, sidebar_pos - 3, footer_pos, sidebar_pos, 0, 0, footer.log, sidebar, map };

  int kolacu = 15;
  int klaciku = 15;

  while (kolacu--) {
    map.random_item(KOLAC);
  }

  while (klaciku--) {
    map.random_item(KLACIK);
  }

  core::InputManager manager;

  Player kuratko{KURATKO, sidebar, 5, 3, M, N};
  map(kuratko.x, kuratko.y) = KURATKO;

  map_window.kuratko = &kuratko;

  Player prasatko{PRASATKO, sidebar, 1, 3, M, N};
  map(prasatko.x, prasatko.y) = PRASATKO;

  auto f = [&kuratko, &map](core::InputAction c) {
    switch (c) {
      case core::InputAction::Left:
      case core::InputAction::Up:
      case core::InputAction::Down:
      case core::InputAction::Right:
        kuratko.move(map, from_action(c));
        break;
      case core::InputAction::Quit:
        // TODO - handle exit gracefully, instead of calling exit
        exit(0);
        break;

      default:
        // TODO - better logging
        cerr << "Unrecognized input character '";
        // cerr << "Unrecognized input character '" << c << "'" << endl;
    }
  };

  manager.add(f);

  thread t(tapkat, ref(prasatko), ref(map));
  thread t2(kolace, ref(map));

  game_loop(manager, map_window);

  t.join();
  t2.join();
}

static void tapkat(Player& prasatko, core::Map& map) {
  while (1) {
    this_thread::sleep_for(chrono::milliseconds(800));
    map.pathfind(prasatko);
  }
}

static void kolace(core::Map& map) {
  while (1) {
    this_thread::sleep_for(chrono::seconds(5));
    map.random_item(KOLAC);
  }
}

