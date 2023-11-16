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
#define MAX_PERM 1000

typedef struct board {
   char chessboard[MAX_BOARD][MAX_BOARD];
} board;


//Initialise the parent board
void emptyBoard(board *b, int board_size);

//Print any board
void printBoard(board *b, int board_size);


// //Initialise the queen array
// void q_arr(queen_array *t, int board_size);

// //Print array of queens with its index and position
// void printQ(queen_array *q, int board_size);

//Deep copy the parent board to child board
void deepCopy(board *original, board *copy, int board_size);

//Check if placement is within bounds
bool in_bound(board *b, int board_size);

//Check if the row or column is safe
bool isSafe_RC(board *b, int board_size, int row, int col);

//Function to check if one queen is safe for any diagonal direction
bool Q_DiagSafe(board b*, int Q_Row, int Q_Col, int B_Row, int B_Col, int board_size);

//Function to check if all N queens are safe, using Q_DiagSafe to check each Queen 
bool QAll_DiagSafe(board *b, int board_size);

//Last function that combines check for in_bound, isSafe_RC, Q_DiagSafe, DiagSafe
bool isSafe(board *b, int board_size, int row, int col);

void test(void);
