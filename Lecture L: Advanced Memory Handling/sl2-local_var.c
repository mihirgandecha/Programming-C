//Local Variables

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LINE 500

char* nify(char s[]);

int main(void)
{
    char* s1 = nify("inconveniencing");
    char* s2 = nify("neill");
    //pointing to memory with string inside it
    assert(strcmp(s2, "Neill") == 0);
    assert(strcmp(s1, "iNcoNveNieNciNg") == 0);
    return 0;
}

// Local copy: Swaps all 'n'-> 'N'
char* nify(char s[])
{
    //temporary array
    char t[LINE];
    strcpy(t, s);
    //change elements of t
    for (int i = 0; t[i]; i++) {
        if (t[i] == 'n') {
            t[i] = 'N';
        }
    }
    //function torn down
    //Out of scope
    // return t;
}
