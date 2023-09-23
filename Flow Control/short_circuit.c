#include <stdio.h>
#include <math.h>

#if 0
int main(void)
{
//Short-Circuit Evaluation Slide

/*Bullet Point 2: 
Truthiness - any value that is not explicitly false is considered true
Used to validate user input. For instance when using scanf(), truthiness
checks that user entered a valid input */

int number;

printf("Enter a number: ");
scanf("%d", &number);

if(number) { //Essentially if number is FALSE (0) being FALSE, and 1 being TRUE)
    printf("The number is invalid.\n");
}

return 0;
}
#endif

//Short-Circuit Evaluation
int main(void)

{
    int x = 0;
    printf("Enter a number please: ");
    scanf("%d", &x);

    if (x >= 0.0 && sqrt(x) 10.0){
        printf("Your test is TRUE");
    }
    else
        printf("Your test is FALSE");
    return 0;
}

