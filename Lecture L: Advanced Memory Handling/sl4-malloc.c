//using malloc()
//Can i have memory that doesn't go away till I say?
//Take home: malloc() you get memory that is always in scope. You are responsible for freeing it up!
//Therefore free up using free()
//Otherwise leaks! We cannot keep calling malloc! WORSE THAN BUGS!
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char* nify(char s[]);

int main(void)
{
    char* s1 = nify("inconveniencing");
    char* s2 = nify("neill");
    assert(strcmp(s2, "Neill") == 0);
    assert(strcmp(s1, "iNcoNveNieNciNg") == 0);
    free(s1);
    free(s2);
    return 0;
}

// malloc : Swaps all 'n'-> 'N'
char* nify(char s[])
{
    int l = strlen(s);
    char* t = (char*)malloc(l+1); //why +1? null charc! therefore string!
    if(t==NULL){
        exit(EXIT_FAILURE);
    }
    strcpy(t, s);
    for(int i=0; t[i]; i++){
        if(t[i] == 'n'){
            t[i] = 'N';
        }
    }
    return t;
}
