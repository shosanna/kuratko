#include <ncurses.h>
#include "map.h"
#include "game.h"

struct Enable_curses {
  Enable_curses() { initscr(); }
  ~Enable_curses() { endwin(); }
};


int main() {
  Enable_curses c;

  const size_t M = 30;
  const size_t N = 30;

  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, false);
  keypad(stdscr, TRUE);

  game_init_colors();

  WINDOW* win = newwin(M+10, N+10, 0, 0);
  scrollok(win, TRUE);

  Log log{M+1, 0, 10, 10};

  Map map{log,M,N};
  map.reset();

  Player kuratko{KURATKO, 5, 6, M, N};
  map(kuratko.x, kuratko.y) = KURATKO;

  Player prasatko{PRASATKO, 22, 3, M, N};
  map(prasatko.x, prasatko.y) = PRASATKO;

  map(23,3) = KOLAC;
  map(21,3) = KOLAC;
  map(21,5) = KOLAC;
  map(23,1) = KOLAC;
  map(21,1) = KOLAC;
  map(2,20) = KOLAC;
  map(8,16) = KOLAC;

  // map(5, 5) = ENEMY;
  // WINDOW* win = newwin(M+10, N+10, 0, 0);

  game_loop(log, kuratko, prasatko, win, map);
}



