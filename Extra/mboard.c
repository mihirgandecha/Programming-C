#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXSQ 10

typedef struct board {
   int grid[MAXSQ][MAXSQ];
   int w;
   int h;
   int totmines;
} board;

#define UNK  '?'
#define MINE 'X'

board make_board(int totmines, int width, int height, char inp[MAXSQ*MAXSQ+1]);


int main(void) {
  char str[MAXSQ*MAXSQ+1];
  strcpy(str, "X100110010001100100011001");

  board b = make_board(1, 8, 3, str);

  // Print the 8x3 2D array
  for (int i = 0; i < b.h; i++) {
    for (int j = 0; j < b.w; j++) {
      printf("%c", b.grid[i][j]);
    }
    printf("\n");
  }

  return 0;
}

board make_board(int totmines, int width, int height, char inp[MAXSQ*MAXSQ+1]) {
  board b;
  b.w = width;
  b.h = height;
  b.totmines = totmines;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      b.grid[i][j] = (int)inp[i * width + j];
    }
  }

  return b;
}
