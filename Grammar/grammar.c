#include <stdio.h>

int main (void){

    int i = 0; int power = 1;

    while(i++ < 10){
        printf("%5i", power *= 2);
    }

printf("\n");

    return 0;
}