#include "ms.h"
#define int_to_char(i) ('0' + (i))
#define char_to_int(j) ((j) - '0')   

// Maybe some of your own function prototypes here

//function for initialising?
int string_check(char* inp, int max_len);

int count_mines(char* inp, int max_len);
int count_unknown(char* inp, int max_len);

int unknown_around_cell(board b, int x, int y);
int mines_around_cell(board b, int x, int y);

board applyRuleOne(board b);
board applyRuleTwo(board b);

bool apply_rules(board* b, bool* board_changed);

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
      unknown_count++;
    }
  }

  return unknown_count;
}

//Function for counting unknown around grid when we find a '?'
int unknown_around_cell(board b, int x, int y){
  int unknown = 0;
  //Loop to check surrounding cell (3 x 3 with UNK in middle)
  for (int point_a = -1; point_a <= 1; point_a++){
    for (int point_b = -1; point_b <= 1; point_b++){
      int newpoint_a = x + point_a; 
      int newpoint_b = y + point_b;

      //Check newpoint_a and newpoint_b is within board width and height
      if(
        (newpoint_a >= 0 && newpoint_a < b.h) &&  
        (newpoint_b >= 0 && newpoint_b < b.w) &&
        //Check if cell is unknown
        (b.grid[newpoint_a][newpoint_b] == UNK)
        ) {
          unknown++;
        } 
    }
  }
  
  return unknown;
}

//Function for counting unknown around grid when we find a '?'
int mines_around_cell(board b, int x, int y){
  int mines = 0;
  //Loop to check surrounding cell (3 x 3 with UNK in middle)
  for (int point_a = -1; point_a <= 1; point_a++){
    for (int point_b = -1; point_b <= 1; point_b++){
      int newpoint_a = x + point_a; 
      int newpoint_b = y + point_b;

      //Check newpoint_a and newpoint_b is within board width and height
      if(
        (newpoint_a >= 0 && newpoint_a < b.h) &&  
        (newpoint_b >= 0 && newpoint_b < b.w) &&
        //Check if cell is mine
        (b.grid[newpoint_a][newpoint_b] == MINE)
        ) {
          mines++;
        } 
    }
  }
  
  return mines;
}

board applyRuleOne(board b){
  for (int j = 0; j < b.h; j++){
    for (int i = 0; i < b.w; i++){
      if (b.grid[i][j] == UNK){
        int mines = mines_around_cell(b, i, j);
        if (mines == b.totmines){

          b.grid[i][j] = int_to_char(mines);
        }
      }
    }
  }
  return b;

}

board applyRuleTwo(board b) {
  for (int j = 0; j < b.h; j++){
    for (int i = 0; i < b.w; i++){
      char current_cell = b.grid[i][j];
      
      if ((current_cell != 'X') && (current_cell != '?')){
        int mines = mines_around_cell(b, i, j);
        int unknowns = unknown_around_cell(b, i, j);
        int total = char_to_int(current_cell);

      if((total - mines) == unknowns){
        
        for (int point_i = -1; point_i <= 1; point_i++){
          for (int point_j = -1; point_j <= 1; point_j++){
            int newpoint_i = i + point_i; 
            int newpoint_j = j + point_j;

            if(
              (newpoint_j >= 0 && newpoint_j < b.h) &&  
              (newpoint_i >= 0 && newpoint_i < b.w) &&
              b.grid[newpoint_i][newpoint_j] == UNK){
                
                b.grid[newpoint_i][newpoint_j] = MINE;
              }      
            }
          }
        }
      }
    }
  }

  return b;
}

bool apply_rules(board* b, bool* board_changed) {
  
  *board_changed = false;
  board previous_state = *b;

  *b = applyRuleOne(*b);
  *b = applyRuleTwo(*b);

  for (int i = 0; i < b->h; i++) {
    for (int j = 0; j < b->w; j++) {
      if(b->grid[i][j] != previous_state.grid[i][j]) {
        *board_changed = true;
        return *board_changed; // return true as soon as a change is detected
      }
    }
  }
  return *board_changed; // return the status of board_changed
}


board solve_board(board b){

  bool board_changed;
  
  do {
    apply_rules(&b, &board_changed);
  } 
  while (board_changed);

  return b;
}

void board2str(char s[MAXSQ*MAXSQ+1], board b){
  for (int i = 0; i < b.h; i++){
    for(int j = 0; j < b.w; j++){
      s[i * b.w + j] = b.grid[i][j];
    }
  }
}


bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]){

if ((width > MAXSQ) || (height > MAXSQ)){
  return false;
}

//Where width and height = 0
if ((width == 0) && (height == 0)){
  return max_len == 0;
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
int mine_string = count_mines(inp, max_len -1);

if ((unsigned)mine_string > totmines){
  return false;
}


return true;
}

// Returns a board based on the totmines, width, height and grid (passed as a string)
board make_board(int totmines, int width, int height, char inp[MAXSQ*MAXSQ+1]){
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

void test(void){
  
  //string_check
  assert(string_check("012345?X6789", 11) == 1);
  assert(string_check("12345abX?8" 11) == 0);
  
}
