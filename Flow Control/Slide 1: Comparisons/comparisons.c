#include <stdio.h>
#include <math.h>

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

int number2;

printf("Enter a number: ");
scanf("%d", &number2);

if(!number2) { //Essentially if number is FALSE (0) being FALSE, and 1 being TRUE)
    printf("The number is invalid.\n");
}

return 0;
}

//If you input numbers 0, 5 - this program should not display anything as it is FALSE, then number2 is TRUE but ! becomes FALSE