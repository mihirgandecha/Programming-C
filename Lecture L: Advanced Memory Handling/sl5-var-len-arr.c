//Variable Length Arrays

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
    int n = strlen(s) + 1;
    char t[n];
    //deep copy: THIS IS NOT ALLOWED!!!
    //-Wvla (this doesn't allow!)
    //memory comes of stack - not heap! therefore function call does not work!
    strcpy(t, s);
    printf("%s%s\n", s, t);
    return 0;
}
//IT WILL CRASH CODE!