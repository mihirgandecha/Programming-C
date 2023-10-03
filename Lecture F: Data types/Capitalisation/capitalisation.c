// Outputs characters twice
#include <stdio.h>

#define CAPS ('A' - 'a') 
//which is 32

int main(void) {
    int c;
    while ((c = getchar()) != EOF) {
        if (c >= 'a' && c <= 'z') { 
//if c is a lower case letter
            putchar(c + CAPS); //could be c - 32 (havent done line this so it is clearer and so we don't need to know ASCII code!
//add a value to c, 
        } else {
            putchar(c);
        }
    }
    putchar('\n');

    return 0;
}
