//Program that looks at all positive triple of numbers that adds up to 7. For instance, 0+0+7 = 7

#include <stdio.h>
#define N 7 

int main(void){

        int cnt = 0, i, j, k;

        for(i = 0; i <= N; i++){ //test that i is less or equal to 7, then add one to i
            for(j = 0; j <= N, j++){ //STEP 3: Now k = 0. So (0, 1, 0).
                for(k = 0; k <= N; k++){ //(STEP 1) k is now 1. is k <= 7? YES. THEN is 0+0+1=7. NO. RUNS till k = 7. THEN 0,0,7 is first output. NOW k = 8. TEST FAILS as 8 is not <= 7. NOW STEP 2.
                    
                    if(i + j + k == N){
                        ++cnt; //just keeping track of triples successfully found
                        printf("%3i%3i%3i\n", i, j, k);
                    }


                } //STEP 2: k test fails and we hit end of j loop. NOW j is 1. So (0, 1, 8). STEP 3.

            } //



        }
    printf("\nCount: %i\n", cnt);


    return 0;
}