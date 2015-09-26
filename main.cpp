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

  Player p{5, 10, M, N};

  Map map{M,N};
  map.reset();

  map(10, 15) = ENEMY;

  printf("\e]12;%s\a", "yellow");
  WINDOW* win = newwin(M+10, N+10, 0, 0);
  wmove(win, p.y, p.x);

  map.print(win);

  game_loop(p, win, map);
}



