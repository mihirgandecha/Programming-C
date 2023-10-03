#include <stdio.h>
#include <math.h>

int conversion(double x);

int main(void){

    double a;
    printf("Enter a real number: ");
    if (scanf("%lf\n", &a) != 1){
        printf("This is not a valid real number!");
        return 1;
    }

    int d = conversion(a);

    printf("%lf\n", a);

    return 0;
}

int conversion(double x){
    (double)1- pow(sin(x), (double)2) + pow(cos(x), (double)2);
    return x;
}