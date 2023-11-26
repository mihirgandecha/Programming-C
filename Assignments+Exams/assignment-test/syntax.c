#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXSQ 10
#define UNK  '?'
#define MINE 'X'

typedef struct board {
   int grid[MAXSQ][MAXSQ];
   int w;
   int h;
   int totmines;
} board;


int string_check(char* inp, int max_len);
int count_mines(char* inp, int max_len);
bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1]);

int main(void){
    board b;
    char str[MAXSQ*MAXSQ+1];
    strcpy(str, "11?010?"); //copy into
    syntax_check(8, 3, 3, str);
}


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

int count_mines(char* inp, int max_len){
  int mine_count = 0;

  for(int i = 0; i < max_len; i++){
    if(inp[i] == 'X'){
      mine_count++;
    }
  }

  return mine_count;
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