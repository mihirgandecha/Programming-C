/* Compute the Volume of a Sphere to the nearest integer */
#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

int main(void) {
    double r;
    printf("Enter a radius: ");
    if(scanf("%lf", &r) == 0){
        printf("Invalid input!\n");
        return 1;
    }
 //check scanf returns a number!!! IF()

    // Make sure radius is positive
    r = fabs(r);

    double a = 4.0 / 3.0 * PI * pow(r, (double)3);

    printf("Volume of your ball = %f\n", a);
    printf("Volume of your ball = %.2f\n", a); //2 Decimal Places - number doesnt change!
    printf("Volume of your ball = %i\n", (int)a); //forcing cast to integer
    printf("Volume of your ball = %.0f\n", a);
    printf("Volume of your ball = %f\n", round(a));
//round() function returns rounded function, or print out to no DP!
    return 0;
}
