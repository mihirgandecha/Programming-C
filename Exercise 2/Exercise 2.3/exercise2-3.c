//Writing a program to approximate PI

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int algorithm(int a);

int main(void){

    double interval = 0;
    printf("Interval: ");
    if(scanf("%lf", &interval) != 1){
        printf("Invalid interval number!");
        return 1;
    }
    double temp = algorithm(interval);
    printf("%lf", temp); 
    return 0;
}

    int algorithm(int a){

    /*double circle_points = 0;
    double square_points = 0;*/
    double rand_x, rand_y;


    //initialise rand() for point x and y
    rand_x = rand();
    rand_y = rand();

    printf("x: %lf y: %lf", rand_x, rand_y);  

    return a;

}