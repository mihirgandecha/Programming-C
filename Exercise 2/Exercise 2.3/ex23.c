//Writing a program to approximate PI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#define INTERVAL 1000

double algorithm();
void test(void);

int main(void){

    double answer = algorithm();
    printf("%lf", answer);

    test();

    return 0; 
}

    double algorithm(){

    int circle_points = 0;
    int square_points = 0;
    double rand_x, rand_y;
    double d;
    double PI;

    for (square_points = 0; square_points < INTERVAL; ++square_points){

        rand_x = ((double)rand()/ (double)RAND_MAX);
        rand_y = ((double)rand()/(double)RAND_MAX);

        d = pow(rand_x, (double)2) + pow(rand_y, (double)2);

        if (d <= 1){
            circle_points++;
        }

    }
    
    PI = 4 * ((double)circle_points / (double)square_points);

    printf("Final Estimation of Pi = %lf\n", PI);
    return PI;

}

void test(void){

    double test_pi = algorithm(INTERVAL);
    assert(test_pi > 1);
    assert (test_pi >= 3.1); //prints the tests too! How can I silence? Check rand() function is it correct?
}
