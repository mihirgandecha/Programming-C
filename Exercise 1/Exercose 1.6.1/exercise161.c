#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    int median = RAND_MAX/2; //checking if each number is above or below the median which is RAND_MAX/2 (midpoint)
    int minus_cnt = 0;
    int plus_cnt = 0;
    int difference;
    

    for (int i = 0; i < 500; ++i) {
        
        if (rand() < median){ //the midpoint
            ++minus_cnt;
        }
        else{
            ++plus_cnt;
        }

    difference = plus_cnt - minus_cnt;

    printf("After %d iterations, difference: %d\n", i, difference);
    
    }

return 0;

}
//completed in 1 hour 5 mins with chatgpt help. Difficult part was realising rand_max / 2. 
//do similar exercise.