#include <stdio.h>
#include <string.h>

#define SWAP(A,B) {char temp = *A; *A = *B; *B = temp;}

void permutate(char* a, int start, int end);

int main(void){

    char str[] = "ABC";
    int n = strlen(str);
    permutate(str, 0, n - 1);
    return 0;
}

void permutate(char* a, int start, int end)
{
    if (start == end){
        printf("%s\n", a);
        return;
    }
    for (int i = start; i <= end; i++){
        SWAP((a + start), (a + i)); //bring one char to front
        permutate(a, start + 1, end);
        SWAP((a+start), (a+end)); //backtrack
    }
}
