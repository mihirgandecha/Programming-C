#include "ms.h"

// Maybe some of your own function prototypes here

//print board function? y only after finished!
//inform the user of the rules?

check_str(char*){

}

/*board solve_board(board b)
{
}*/

/*void board2str(char s[MAXSQ*MAXSQ+1], board b)
{
}*/

bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1])
{
    //Check if width is > MAXSQ - good practice to say why false?
    if ((width || height) > MAXSQ){
      return false;
    }
// Ensure only characters are from the set:   0123456789?X

// Ensure mines in string <= totmines



// Make sure number of characters in string == width*height
  int max_len = strlen(width * height) + 1;
  check_str();

}

// Returns a board based on the totmines, width, height and grid (passed as a string)
board make_board(int totmines, int width, int height, char inp[MAXSQ*MAXSQ+1])
{
    //Initialise board objects.
    board b;
    b.w = width;
    b.h = height;
    b.totmines = totmines;

    //Initialise board grid (1D Arr -> 2D Arr)
    for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      b.grid[i][j] = (int)inp[i * width + j];
    }
  }

  return b;
}

/*void test(void)
{
}*/