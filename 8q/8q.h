#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_BOARD 10
#define EMPTY 'X'
#define QUEEN 'Q'
#define OUT_BOUNDS -1

typedef struct queen_array {
    int board_size;
    char queen[MAX_BOARD];
    int q_index[MAX_BOARD];
    int row[MAX_BOARD];
    int col[MAX_BOARD];
} queen_array;

typedef struct board {
   char chessboard[MAX_BOARD][MAX_BOARD];
} board;

void q_arr(queen_array *t, int board_size);
void emptyBoard(board *b, int board_size);
void printBoard(board *b, int board_size);
bool in_bound(board *b, int board_size);
void test(void);
