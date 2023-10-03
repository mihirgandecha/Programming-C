// Outputs characters twice
#include <stdio.h>

int main(void) {
    char c;

    do {
        c = getchar();
        putchar(c);
        putchar(c); //prints doubles of input
    } while (c != '!'); //stops when input is !

    putchar('\n');

    return 0;
}
//had to kill terminal as it kept going when multi-line used!