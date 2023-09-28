//Suppose that you hate even integers but love odd ones.

#include <stdio.h>

int main(void) {
    int total_num, result;
    double number, largest;

    printf("Please only enter odd integers.\n");
    printf("How many numbers do you want to input? ");
    result = scanf("%i", &total_num);

    if (result != 1 || total_num <= 0 || total_num % 2 == 0) {
        printf("Invalid number\n");
        return 1;  // Terminating the program 
    }

    printf("Enter a real number: ");
    scanf("%lf", &number);  // our first number

    if ((int)number % 2 == 0){ //have to cast to make number an integer
        printf("Invalid number.\n");
        return 2;
    }
    else{
    largest = number;  // setting the first number as the largest
    }


    for (int i = 1; i < total_num; ++i) {  // looping here, we have 1 number from user amd looping an IF to see if the previous number is larger
        printf("Enter a real number: ");
        scanf("%lf", &number);
        
        if ((int)number % 2 == 0){ //have to cast to make number an integer
        printf("Invalid number.\n");
        return 3;
        }

        else {
            if (number > largest) {
            largest = number;
        }
        }
    }

    printf("The largest number is: %lf\n", largest);

    return 0;
}

//Learnt that you need to declare integer (like line 21) to convert