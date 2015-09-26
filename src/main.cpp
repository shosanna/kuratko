#include <ncurses.h>
#include "map.h"
#include "game.h"

struct Enable_curses {
  Enable_curses() { initscr(); }
  ~Enable_curses() { endwin(); }
};


int main() {
  Enable_curses c;

  const size_t M = 20;
  const size_t N = 20;

  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, false);
  keypad(stdscr, TRUE);

  game_init_colors();

  WINDOW* win = newwin(M+10, N+10, 0, 0);

  Map map{M,N};
  map.reset();

  Player p{5, 6, M, N};
  map(p.x, p.y) = PLAYER;

  // map(5, 5) = ENEMY;
  // WINDOW* win = newwin(M+10, N+10, 0, 0);

  game_loop(p, win, map);
}



