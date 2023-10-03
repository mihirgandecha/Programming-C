// Outputs characters twice
#include <stdio.h>

int main(void) {
    char c; // char or int ?

    while ((c = getchar()) != EOF) { //get character from the keyboard. While the character is a normal character (as in NOT EOF) continue running.
        putchar(c);
        putchar(c);
    }
    //EOF is great for multi-line input

    putchar('\n');

    return 0;
}
