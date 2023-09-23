#include <stdio.h>

int compute_area(int side1, int side2) {
    int area = side1 * side2; //This is a declaration
    return area;
}

int main(void)

{
    //Computing the area of a rectangle
    int side1, side2;
    printf("Please input the length of the sides of the rectangle: ");
    if(scanf("%i%i", &side1, &side2) != 2){ //If we said side 1 = 2 this is called an assignment. This has 2 arguements, the %i suggests that 2 integers will be printed.
        printf("Wrong input detected.\n");
    return 1;
    }

    int result = compute_area(side1, side2);
    printf("The area of your rectangle is: %i", result);
    return 0;
}