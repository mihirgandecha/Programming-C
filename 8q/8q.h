#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_BOARD 10

typedef struct board {
   int chessboard[MAX_BOARD][MAX_BOARD];
   int row;
   int column;
   int queen;
} board;

void test(void);
