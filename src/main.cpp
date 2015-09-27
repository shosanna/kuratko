#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <string.h>
#include <random>
#include "map.h"
#include "game.h"
#include "window.h"
#include "status.h"

using namespace std;

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

  start_color();
  init_pair(1, COLOR_RED, COLOR_BLUE);

  cbreak();
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


  // TODO - zapnout ASAN

  int sidebar_pos = static_cast<int>(maxx * xratio);
  int footer_pos = static_cast<int>(maxy * yratio);
  size_t M = footer_pos - 2;
  size_t N = sidebar_pos - 2;

  Window mainwin(footer_pos, sidebar_pos, 0, 0);
  mainwin.box();

  Window sidebar(footer_pos, maxx - sidebar_pos, 0, sidebar_pos);
  sidebar.box();

  Window footer(maxy - footer_pos, maxx, footer_pos - 1, 0);
  footer.box();

  mvwprintw(mainwin, 0, 1, "Zviratkovy les");
  mainwin.refresh();
  mainwin.ready_cursor();

  mvwprintw(sidebar, 0, 1, "Status");
  sidebar.refresh();
  sidebar.ready_cursor();

  mvwprintw(footer, 0, 1, "Log");
  footer.refresh();
  footer.ready_cursor();

  scrollok(footer, TRUE);

  wprintw(mainwin, "dalsi");
  mainwin.refresh();

  Log log{ footer };

  game_init_colors();

  Status status{sidebar};

  Map map{ mainwin, log, status, M, N };
  map.reset();

  Player kuratko{KURATKO, status, 5, 3, M, N};
  map(kuratko.x, kuratko.y) = KURATKO;

  Player prasatko{PRASATKO, status, 1, 3, M, N};
  map(prasatko.x, prasatko.y) = PRASATKO;

  int kolacu = 10;

  std::random_device rd;
  std::uniform_int_distribution<size_t> x_dis(0, N-1);
  std::uniform_int_distribution<size_t> y_dis(0, M-1);
  std::mt19937 gen(rd());

  while (kolacu--) {
    map(x_dis(gen), y_dis(gen)) = KOLAC;
  }

  game_loop(kuratko, prasatko, mainwin, map);

  return 0;
}
