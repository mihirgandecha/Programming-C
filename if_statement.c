#include <stdio.h>

int main(void)
{
/*For the if statement, put {} if more than one statement 
is required, otherwise just ()*/

//if (expr) statement
//For instance with if else statement {} are used

    int x, y, z;
/*Here the first if statement is asking for three integers.
IF the user does not (!=) enter three numbers
then printf statement.
*/
    printf("Input three integers: ");
    if(scanf("%i%i%i", &x, &y, &z) != 3){
        printf("Didn't get 3 numbers?\n");
        return 1; //avoids crash
    }

    int min;
    if (x < y){
        min = x;
    }
        else {
            min = y;
        }

        if (z < min){
            min = z;
        }
    printf("The minimum value is %i\n", min);
    return 0;
}