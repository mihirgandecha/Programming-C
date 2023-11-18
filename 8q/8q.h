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
#define MAX_PERM 80000

typedef struct board {
   char chessboard[MAX_BOARD][MAX_BOARD];
} board;

// void appendList(int *list_size, int *board_size);

// WORKS: void appendList(board arrayof_struct[], int *list_size, int *board_size);
void appendList(board solve_list[], int *list_size, int *board_size);

void QNNSolved(board arrayof_struct[], int *list_size, int *board_size);

void nqueenSolved(board solve_list[], int *list_size, int *board_size);

int countQueens(board *b, int board_size);

void printAllBoards(board arrayof_struct[], int *n, int f);
//Initialise the parent board
void emptyBoard(board *b, int board_size);

//Print any board
void printBoard(board *b, int board_size);

//Deep copy the parent board to child board
void deepCopy(board *original, board *copy, int board_size);

//Functions for Q-positioning:
//(1)Check if placement is within bounds
int in_bound(int row, int col, int board_size);

//(2)Check if the row or column is safe
bool isSafe_RC(board *b, int board_size, int row, int col);

//(3)Function to check if queen is safe for any diagonal direction
bool Q_DiagSafe(board *b, int row, int col, int board_size);

//(5)Last function that combines check for in_bound, isSafe_RC, Q_DiagSafe, DiagSafe
bool isSafe(board *temp, int board_size, int row, int col);

//Solving board functions:
//(1)Initialise Q1 placement:
void initialise_Q1boards(board *solve_list, int *b, int board_size);

//(2)Initialise Q2-QN placement given test_QPlacement succeeeds:
void addQN(board *current_board, board *solve_list, int board_size, int *b);

//(3)Check if Q count == board_size
bool isQNSolved(board *b, int board_size);

//(4)Duplicate check:
bool areBoardsIdentical(board *board1, board *board2, int board_size);
bool compareBoard(board *current_board, board solve_list[], int num_boards, int board_size);

//(5)Solve the board:
void solveBoard(board *solve_list, int *b, int *solutions, int board_size, bool *verbose);
//Print solution:
void printBoardSolution(board *b, int board_size);

//Test function
void test(void);
