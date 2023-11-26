#include <stdio.h>
#include <stdlib.h>

//How you use gdb to see mem alloc
int main(void){
    
    int num1;
    int num2;
    double average;
    
    printf("Enter num1: ");
    scanf("%d", &num1);

    printf("Enter num2: ");
    scanf("%d", &num2);

    average = (double)(num1 + num2) / 2;
    printf("Average = %lf\n", average);
    return 0;
}
