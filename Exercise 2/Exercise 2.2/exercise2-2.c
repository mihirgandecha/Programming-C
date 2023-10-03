#include <stdio.h>
#include <math.h>

int conversion(double x);

int main(void){

    double a;
    printf("Enter a real number: ");
    if (scanf("%lf", &a) != 1){
        printf("This is not a valid real number!");
        return 1;
    }

    int d = conversion(a);

    if (d == 0) {
    printf("sin^2(%lf) + cos^2(%lf) is equal to 1.\n", a, a);
    } else {
    printf("sin^2(%lf) + cos^2(%lf) is not equal to 1.\n", a, a);
    }

    return 0;
}

int conversion(double x){

    double solution = 1.0; //Q: is this not an appropriate double? Does it have to be smaller?
    double result = pow(sin(x), (double)2) + pow(cos(x), (double)2);

    printf("The result of sin^2(%lf) +cos^2(%lf) is: %lf\n", x, x, result);
    if (result < solution){
        return 0;
    }
        else{
            return 1;
        }
   
    }
    
