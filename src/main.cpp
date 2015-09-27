#include <ncurses.h>
#include <string.h>
#include "map.h"
#include "game.h"

struct Enable_curses {
  Enable_curses() { initscr(); }
  ~Enable_curses() { endwin(); }
};

struct Window {
  WINDOW* w;
  Window(size_t w, size_t h, size_t x = 0, size_t y = 0): w{newwin(w,h,x,y)} {}
  ~Window() { delwin(w); }

  void box() { ::box(w, 0, 0); refresh(); }
  void refresh() { ::wrefresh(w); }

  operator WINDOW*() { return w; }
};

int main() {
  Enable_curses c__{};

  start_color();
  init_pair(1, COLOR_RED, COLOR_BLUE);

  cbreak();
  keypad(stdscr, TRUE);
  refresh();

  int maxy, maxx;

  getmaxyx(stdscr, maxy, maxx);

  int sidebar_pos = static_cast<int>(maxx * 0.7);
  int footer_pos = static_cast<int>(maxy * 0.8);

  Window mainwin(footer_pos, sidebar_pos, 0, 0);
  mainwin.box();

  Window sidebar(footer_pos, maxx - sidebar_pos, 0, sidebar_pos);
  sidebar.box();

  Window footer(maxy - footer_pos, maxx, footer_pos - 1, 0);
  footer.box();

  mvwprintw(mainwin, 0, 1, "Zviratkovy les");
  mainwin.refresh();

  mvwprintw(sidebar, 0, 1, "Status");
  sidebar.refresh();

  mvwprintw(footer, 0, 1, "Log");
  footer.refresh();

  getch();

//
//    int ch, prev, row, col;
//   prev = EOF;
//   FILE *fp;
//   int y, x;
//
//   if(argc != 2)
//   {
//     printf("Usage: %s <a c file name>\n", argv[0]);
//     exit(1);
//   }
//   fp = fopen(argv[1], "r");
//   if(fp == NULL)
//   {
//     perror("Cannot open input file");
//     exit(1);
//   }
//   initscr();                            #<{(| Start curses mode |)}>#
//   getmaxyx(stdscr, row, col);           #<{(| find the boundaries of the
//   screeen |)}>#
//   while((ch = fgetc(fp)) != EOF)        #<{(| read the file till we reach the
//   end |)}>#
//   {
//     getyx(stdscr, y, x);                #<{(| get the current curser position
//     |)}>#
//     if(y == (row - 1))                  #<{(| are we are at the end of the
//     screen |)}>#
//     {
//       printw("<-Press Any Key->");      #<{(| tell the user to press a key
//       |)}>#
//       getch();
//       clear();                          #<{(| clear the screen |)}>#
//       move(0, 0);                       #<{(| start at the beginning of the
//       screen |)}>#
//     }
//     if(prev == '/' && ch == '*')        #<{(| If it is / and * then only
//                                          * switch bold on |)}>#
//     {
//       attron(A_BOLD);                   #<{(| cut bold on |)}>#
//       getyx(stdscr, y, x);              #<{(| get the current curser position
//       |)}>#
//       move(y, x - 1);                   #<{(| back up one space |)}>#
//       printw("%c%c", '/', ch);          #<{(| The actual printing is done
//       here |)}>#
//     }
//     else
//       printw("%c", ch);
//     refresh();
//     if(prev == '*' && ch == '/')
//       attroff(A_BOLD);                  #<{(| Switch it off once we got *
//                                          * and then / |)}>#
//     prev = ch;
//   }
//   endwin();                             #<{(| End curses mode |)}>#
//   fclose(fp);
//
//
//   // Enable_curses c;
//   //
//   // const size_t M = 30;
//   // const size_t N = 30;
//   //
//   // // cbreak();
//   // // noecho();
//   // // nonl();
//   // // intrflush(stdscr, false);
//   // // keypad(stdscr, TRUE);
//   //
//   // game_init_colors();
//   //
//   // WINDOW* win = newwin(M+10, N+10, 0, 0);
//   // scrollok(win, TRUE);
//   //
//   // Log log{0, 0, 10, 10};
//   //
//   // Map map{log,M,N};
//   // map.reset();
//   //
//   // Player kuratko{KURATKO, 5, 6, M, N};
//   // map(kuratko.x, kuratko.y) = KURATKO;
//   //
//   // Player prasatko{PRASATKO, 22, 3, M, N};
//   // map(prasatko.x, prasatko.y) = PRASATKO;
//   //
//   // map(23,3) = KOLAC;
//   // map(21,3) = KOLAC;
//   // map(21,5) = KOLAC;
//   // map(23,1) = KOLAC;
//   // map(21,1) = KOLAC;
//   // map(2,20) = KOLAC;
//   // map(8,16) = KOLAC;
//   //
//   // log.print(win);
//   //
//   // // map(5, 5) = ENEMY;
//   // // WINDOW* win = newwin(M+10, N+10, 0, 0);
//   //
//   // game_loop(log, kuratko, prasatko, win, map);

  return 0;
}
