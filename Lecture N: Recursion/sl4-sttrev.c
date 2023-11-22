#include <stdio.h>
#include <string.h>

#define SWAP(A,B) {char temp; temp = A; A = B; B = temp;}

void strrev(char* s, int start, int end);

int main(void){

    char str[] = "Hello World!";
    strrev(str, 0, strlen(str) - 1);
    printf("%s\n", str);
    return 0;
}

void strrev(char* s, int start, int end)
{
    if (start >= end){
        return;
    }
    //Rewriting this part:
    // for (int i = 0, j = (n - 1); i < j; i++, j--){
        //looks more readable in this version
    SWAP(s[start], s[end]);
    strrev(s, start + 1, end - 1);
    
}
