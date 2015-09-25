#include <stdlib.h>
#include <stdio.h>

const char* GRAY = "\e[90m";
const char* GREEN = "\e[32m";
const char* RED = "\e[31m";

#define M 20
#define N 40

static char map[M][N];

#define EMPTY '.'
#define PLAYER '@'
#define ENEMY 'x'

void map_reset() {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      map[i][j] = EMPTY;
    }
  }
}

void clear() {
  putchar(27);
  putchar('[');
  putchar('2');
  putchar('J');
}

void map_switch_color(const char* color) { printf("%s", color); }

void map_print() {
  clear();

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
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
    puts("");
  }
}

int main() {
  map_reset();
  map[10][10] = PLAYER;
  map[10][20] = ENEMY;
  map_print();

  while (1) {
    char c = getchar();
    switch (c) {
      default:
        {
          int x = (int)c;
          printf("%d\n", x);
        }
    }
  }
}









