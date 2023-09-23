#include <stdio.h>

int integer_sum(int a, int b, int c){
int sum = ((a + b + c) * 2) + 7;

return sum;
}
int main(void)

{
    int e, f, g;

    printf("Input three integers: ");
    if(scanf("%i%i%i", &e, &f, &g) != 3){
        printf("Error. Please input three integers.\n");
        return 1;
    }


    printf("Twice the sum of integers plus 7 is %i\n", integer_sum(e, f, g));

    return 0;
}