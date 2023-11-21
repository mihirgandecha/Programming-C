#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

// Checks whether a particular string can be typed
// using ONLY the keys on the top row of a keyboard
// i.e. qwertyuiopQWERTYUIOP 
bool toprow(const char s[]);

int main(void)
{

   // We will use these, as well as other, similar examples
   // to test your code with.
    
   // typewriter
   assert(toprow("typewriter")==true);
   // Torque
   assert(toprow("Torque")==true);
   // Equity
   assert(toprow("Equity")==true);
   // empty string
   assert(toprow("")==true);

   // FLASH
   assert(toprow("FLASH")==false);
   // typewriters
   assert(toprow("typewriters")==false);
   // tip-top
   assert(toprow("tip-top")==false);

}

bool toprow(const char s[])
{
    const char *top_row = "qwertyuiopQWERTYUIOP";
    for (int i = 0; (long unsigned)i < strlen(s); ++i){
        if (strchr(top_row, s[i]) == NULL){
            return false;
            } 
        }

    return true;

}
