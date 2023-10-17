#include "ms.h"

// Maybe some of your own function prototypes here

/*board solve_board(board b)
{
}*/

/*void board2str(char s[MAXSQ*MAXSQ+1], board b)
{
}*/

/*bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1])
{
}*/

// Returns a board based on the totmines, width, height and grid (passed as a string)
board make_board(int totmines, int width, int height, char inp[MAXSQ*MAXSQ+1])
{
    //Initialise board objects.
    board new_board;
    b.w = width;
    b.h = height;
    b.totmines = totmines;

    //Initialise board grid (1D Arr -> 2D Arr)
    for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      b.grid[i][j] = (int)inp[i * width + j];
    }
  }

  return new_board;
}

/*void test(void)
{
}*/