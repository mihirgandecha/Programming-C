//Writing a program to approximate PI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#define INTERVAL 10000

double algorithm();

int main(void){

    double answer = algorithm();
    printf("%lf", answer);
    return 0; 
}

    double algorithm(){

    int circle_points = 0;
    int square_points = 0;
    double rand_x, rand_y;
    double d;
    double PI;

    for (square_points; square_points < INTERVAL; ++square_points){

        rand_x = ((double)rand()/ (double)RAND_MAX);
        rand_y = ((double)rand()/(double)RAND_MAX);
        printf("%lf,  %lf\n", rand_x, rand_y);
        d = pow(rand_x, (double)2) + pow(rand_y, (double)2);
        printf("d is: %lf\n", d);

        if (d <= 1){
            circle_points++;
            printf("Circle Points: %i\n", circle_points);
        }

    }
    printf("Circle Points: %i Square Points: %i\n", circle_points, square_points);
    PI = 4 * ((double)circle_points / (double)square_points);

    printf("Final Estimation of Pi = %lf", &PI);
    return PI;

}

void test(void){

    assert( algorithm() > 1);
}
