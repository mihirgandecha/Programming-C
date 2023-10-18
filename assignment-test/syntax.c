#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXSQ 10

typedef struct board {
   int grid[MAXSQ][MAXSQ];
   int w;
   int h;
   int totmines;
} board;

#define UNK  '?'
#define MINE 'X'

syntax_check(unsigned, unsigned, unsigned, char);
int main(void){
    board b;
    char str[MAXSQ*MAXSQ+1];
    strcpy(str, "11?010?"); //copy into
    syntax_check(8, 3, 3, str);
}

bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1])
{
    //Check if width is > MAXSQ - good practice to say why false?
    if ((width || height) > MAXSQ){
      return false;
    }
}
// Ensure only characters are from the set:   0123456789?X
    int max_len = strlen(width * height) + 1;
    char rules[] = {"0123456789?X"};

    for (int i = 0; i < max_len; i++){
        for (int j = 0; j < max_len; j++){
            
        }

        }
        


// Ensure mines in string <= totmines