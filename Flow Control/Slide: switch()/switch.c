#include <stdio.h>

int main (void){

    int i, n;

    do{
        printf("Enter a number from 2-9: ");
        n = scanf("%i", &i);

    } while ((n != 1) || (i < 2) || (i > 9));

    switch (i) {
        case 2:
        case 3:
        case 5:
        case 7:
            printf("That's a prime number!\n");
            break;
        default:
            printf("That is not a prime number!\n");

    }




    return 0;
}