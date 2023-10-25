//Memory Leaks

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define WORD 500

int main(void)
{
    printf("Please type a string :\n");
    char s[WORD];
    assert(scanf("%s", s) == 1);
    int n = strlen(s);

    //deep copy
    char* t = (char*) malloc(n + 1);
    assert(t != NULL); //PANIC IF EQUAL! USE IF STATEMENT!if (t = NULL)
    strcpy(t, s);
    printf("%s%s\\n", s, t);
    return 0;

    //DOES NOT free() memory! compiler does not work!
    //mem leak!
    //Use VALGRIND!
}
