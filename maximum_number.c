#include <stdio.h>

int main(void)

{
    int a, b, c;

    printf("Please enter three values: ");
    if(scanf("%i %i %i", &a, &b, &c) != 3)
        printf("Fail. Please input three integers bro.");

        return 1;
    
    int max;

    if(a > b && a > c){
        max = a;
    }

    if(b > a && b > c){
        max = b;
    }

    else{
        max = c;
    }
    printf("The biggest number out of the three is%i\n", max);
    return 0;
}