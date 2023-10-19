#include "ms.h"

// Maybe some of your own function prototypes here
int string_check(char* inp, int max_len);
int count_mines(char* inp, int max_len);

//Function for checking string is within rules
int string_check(char* inp, int max_len){
  char rules[] = "012345678?X";
  int rules_len = strlen(rules);

  for (int i = 0; i < max_len; i++){
    int rule_broken = 0;
    for (int j = 0; j < rules_len; j++){
      if(inp[i] == rules[j]) {
        rule_broken = 1;
      }
    }
    if (!rule_broken){
      return 0;
    }
  }
  return 1;
}

//Function for counting mines in grid
int count_mines(char* inp, int max_len){
  int mine_count = 0;

  for(int i = 0; i < max_len; i++){
    if(inp[i] == MINE){
      mine_count++;
    }
  }

  return mine_count;
}

//Function for counting unknowns in grid
int count_unknown(char* inp, int max_len){
  int unknown_count = 0;

  for(int i = 0; i < max_len; i++){
    if(inp[i] == UNK){
      count_unknown++;
    }
  }

  return count_unknown;
}

//Function for counting unknown around grid when we find a '?'
int UNKaround_cell(board b, int a, int b){
  int unknown = 0;
  //Loop to check surrounding cell

}


/*board solve_board(board b)
{
}*/

void board2str(char s[MAXSQ*MAXSQ+1], board b)
{
  for (int i = 0; i < b.h; i++){
    for(int j = 0; j < b.w; j++){
      s[i * b.w + j] = b.grid[i][j];
    }
  }
}


bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1])
{

if ((width > MAXSQ) || (height > MAXSQ)){
  return false;
}

int max_len = strlen(inp);
int board_len = width * height;

// Make sure number of characters in string == width*height
if (max_len != (board_len + 1)){ //check +1
  return false;
}

// Ensure only characters are from the set:   0123456789?X
return string_check(inp, max_len);
  
// Ensure mines in string <= totmines
int mine_string = count_mines(inp, max_len);

if ((unsigned)mine_string > totmines){
  return false;
}


return true;
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

void test(void)
{
}

