#include "toprow.h"

bool toprow(const char s[])
{
    const char *top_row = "qwertyuiopQWERTYUIOP";
    for (int i = 0; i < strlen(s); ++i){
        if (strchr(top_row, s[i]) == NULL){
            return false;
            } 
        }

    return true;

}
