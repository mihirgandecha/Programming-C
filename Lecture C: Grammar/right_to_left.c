#include <stdio.h>

int main(void){

    int a = 0, b = 0;

    a = 1 + 2 + 3;
    b += 3;

    printf("a is equal to %i and b is equal to %i\n", a, b);

    int c, d, e;

    c = d = e = 5; //Equal to c = (d = (e = 0)). Right to left operation!

    printf("%i, %i, %i\n", c, d, e); 

    return 0;
}