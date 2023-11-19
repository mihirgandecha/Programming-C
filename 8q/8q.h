#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_BOARD 10
#define EMPTY 'X'
#define QUEEN 'Q'
#define IN_BOUND 1
#define OUT_BOUNDS -1
#define MAX_PERM 50000

typedef struct board {
   char chessboard[MAX_BOARD][MAX_BOARD];
} board;

//Solve NQueen Functions
//Initialises an empty board with 'X'
void emptyBoard(board *b, int board_size);

//Creates a deep copy of boards taking orignal->copy
void deepCopy(board *original, board *copy, int n);

//Checks if a given row and column is in bounds of the board
int in_bound(int row, int col, int board_size);

//Checks if a given row and column is safe from other queens
bool isSafe_RC(board *b, int board_size, int row, int col);

//Checks if a given row and column is safe from other queens diagonally
bool Q_DiagSafe(board *b, int row, int col, int board_size);

//Checks if a given row, column is safe (in-bound too) from other queens
bool isSafe(board *temp, int board_size, int row, int col);

//Finds the maximum number of permutations for a given board size
int getMaxPerm(int board_size);

//Creates list of all possible boards
void nqueenSolved(board solve_list[], int *list_size, int *board_size);

//Counts the number of queens on a board
int countQueens(board *b, int board_size);

//Checks if two boards are identical
bool areBoardsIdentical(board *board1, board *board2, int board_size);

//Checks if a board is already in the list of boards
bool compareBoard(board *current_board, board solve_list[], int num_boards, int board_size);

//Prints the board solution if -verbose flag is used
void printBoardSolution(board *b, int board_size);

//Solves the n-queens problem taking all inputs and functions
void solveNQueens(int n, int verbose);

//Test function
void testEmptyBoard(int n);
void testDeepCopy(int n);
//tests for queen rules: 
void testin_bound(void);
void test_isSafeRC(void);
void test_QDiagSafe(void);
void test_isSafe(void);

void test(void);
