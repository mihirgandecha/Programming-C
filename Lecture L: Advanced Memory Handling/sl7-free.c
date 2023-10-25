//Using free()
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define WORD 500

int main(void)
{
    char s[WORD] = "String";
    int n = strlen(s);
    char* t = (char*) malloc(n + 1);
    assert(t != NULL);
    strcpy(t, s);
    printf("%s%s\n", s, t);
    free(t);
    return 0;
} 
/*FOR Final Check: 
use optimiser, 
use sanitizer flag, 
use valgrind!*/
