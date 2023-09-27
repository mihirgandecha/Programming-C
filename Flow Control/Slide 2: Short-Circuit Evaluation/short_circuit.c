//Program tests that the number isn't negative - as negative numbers can't square root!!!

#include <stdio.h>
#include <math.h>

int main() {
    double x; 

    printf("Enter a value for x: ");
    scanf("%lf", &x);

    if (x >= 0.0 && sqrt(x) < 10.0) {
        // Do something
        printf("The condition is true!\n");
    }

    return 0;
}

//remember using sqrt uses different compiling process
//clang short_circuit.c -o short_circuit -lm
