#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

struct Enable_curses {
  Enable_curses() { initscr(); }
  ~Enable_curses() { endwin(); }
};

using namespace std;

const char* GRAY = "\e[90m";
const char* GREEN = "\e[32m";
const char* RED = "\e[31m";

constexpr size_t M = 20;
constexpr size_t N = 40;

static char map[M][N];

constexpr char EMPTY = '.';
constexpr char PLAYER = '@';
constexpr char ENEMY = 'x';

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Player {
 public:
  size_t x = 0;
  size_t y = 0;

  Player() = default;
  Player(size_t x, size_t y) : x(x), y(y) {}

  void move(WINDOW* win, Direction dir) {
    mvwaddch(win, y, x, EMPTY);
    switch (dir) {
      case Direction::UP:
        --y;
        break;
      case Direction::DOWN:
        ++y;
        break;
      case Direction::LEFT:
        --x;
        break;
      case Direction::RIGHT:
        ++x;
        break;
    }
    mvwaddch(win, y, x, PLAYER);
    wmove(win, y, x);
  }
};

void map_reset() {
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      map[i][j] = EMPTY;
    }
  }
}

void map_clear() { cout << static_cast<char>(27) << "[2J"; }

void map_switch_color(const char* color) { cout << color; }

void map_print() {
  stringstream ss;
  map_clear();

  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < N; j++) {
      char curr = map[i][j];

      switch (curr) {
        case PLAYER:
          map_switch_color(GREEN);
          break;

        case EMPTY:
          map_switch_color(GRAY);
          break;

        case ENEMY:
          map_switch_color(RED);
      }

      putchar(curr);
    }
    putchar('\n');
  }
}

int main() {
  Enable_curses c;

  map_reset();
  map[10][10] = PLAYER;
  map[10][20] = ENEMY;

  cbreak();
  noecho();
  nonl();
  intrflush(stdscr, false);
  keypad(stdscr, TRUE);

  Player p;
  WINDOW* win = newwin(M, N, 0, 0);

  wmove(win, p.y, p.x);
  wrefresh(win);

  while (1) {
    char c = getchar();

    switch (c) {
      case 'h':
        p.move(win, Direction::LEFT);
        break;
      case 'k':
        p.move(win, Direction::UP);
        break;
      case 'j':
        p.move(win, Direction::DOWN);
        break;
      case 'l':
        p.move(win, Direction::RIGHT);
        break;
      case 'q':
        exit(0);
    }

    // waddch(win, 'f');
    //
    // wmove(win, player_y, player_x);

    wrefresh(win);
  }
}
