#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_BOARD 10
#define EMPTY -1

typedef struct board {
   int chessboard[MAX_BOARD][MAX_BOARD];
} board;

int parentBoard(board *b, int n);
void test(void);
