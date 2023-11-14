#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_BOARD 10
#define EMPTY 'X'
#define QUEEN 'Q'

typedef struct board {
   char chessboard[MAX_BOARD][MAX_BOARD];
   int queen_count;
   int empty_count;
   int nposib;
   char queen_array[n] = {};
} board;

int parentBoard(board *b, int n);
void test(void);
