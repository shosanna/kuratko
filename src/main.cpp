#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <string.h>
#include <random>
#include <thread>

#include "map.h"
#include "game.h"
#include "core/input_manager.h"

#include "gui/log_window.h"
#include "gui/status_window.h"
#include "gui/window.h"

using namespace std;
using namespace kuratko;

void game();
static void tapkat(Player& prasatko, Map& map);
static void kolace(Map& map);

struct Enable_curses {
  Enable_curses() {
    initscr();
  }
  ~Enable_curses() {
    endwin();
  }
};

int main() {
  Enable_curses c__{};
  game();

  return 0;
}

void game() {
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

  gui::Window mainwin(footer_pos, sidebar_pos, 0, 0);
  mainwin.box();
  mainwin.refresh();

  gui::StatusWindow sidebar(footer_pos, maxx - sidebar_pos, 0, sidebar_pos);
  sidebar.box();
  sidebar.refresh();

  gui::LogWindow footer(maxy - footer_pos, maxx, footer_pos - 1, 0);
  footer.ready_cursor();
  footer.refresh();

  mvwprintw(mainwin, 0, 1, "Zviratkovy les");
  mainwin.refresh();
  mainwin.ready_cursor();

  scrollok(footer, TRUE);

  game_init_colors();

  Map map{ mainwin, footer.log, sidebar, M, N };
  map.reset();

  int kolacu = 5;
  int klaciku = 3;

  while (kolacu--) {
    map.random_item(KOLAC);
  }

  while (klaciku--) {
    map.random_item(KLACIK);
  }

  core::InputManager manager;

  Player kuratko{KURATKO, sidebar, 5, 3, M, N};
  map(kuratko.x, kuratko.y) = KURATKO;

  Player prasatko{PRASATKO, sidebar, 1, 3, M, N};
  map(prasatko.x, prasatko.y) = PRASATKO;

  auto f = [&kuratko, &map](int c) {
    switch (c) {
      case 'a':
      case KEY_LEFT:
      case 'h':
        kuratko.move(map, Direction::LEFT);
        break;
      case 'w':
      case KEY_UP:
      case 'k':
        kuratko.move(map, Direction::UP);
        break;
      case 's':
      case KEY_DOWN:
      case 'j':
        kuratko.move(map, Direction::DOWN);
        break;
      case 'd':
      case KEY_RIGHT:
      case 'l':
        kuratko.move(map, Direction::RIGHT);
        break;
      case 'q':
        exit(0);
    }
  };

  manager.add(f);

  thread t(tapkat, ref(prasatko), ref(map));
  thread t2(kolace, ref(map));

  game_loop(manager, mainwin, map);

  t.join();
  t2.join();
}

static void tapkat(Player& prasatko, Map& map) {
  while (1) {
    this_thread::sleep_for(chrono::milliseconds(800));
    map.pathfind(prasatko);
  }
}

static void kolace(Map& map) {
  while (1) {
    this_thread::sleep_for(chrono::seconds(5));
    map.random_item(KOLAC);
  }
}

