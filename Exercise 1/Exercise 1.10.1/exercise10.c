#include <stdio.h>

int main(void){
    int A = 0;
    int C = 0;
    int M = 0;
    int SEED = 0;

    int found_repeat = 0;

    printf("What numbers would you like to input into the LCG loop? A =  C =  M =");
    scanf("%i%i%i", &A, &C, &M);

    int current_seed = SEED;

    for(int i = 0; i < M && !found_repeat; i++){ //initialising counter i
        current_seed = (A * current_seed + C) % M;

        int check_repeats_seed = current_seed; 
        for(int j = i + 1; j < M && !found_repeat; j++){ 
            check_repeats_seed = (A * check_repeats_seed + C) % M;

            if (current_seed == check_repeats_seed) {
                found_repeat = 1;
                printf("The sequence starts repeating after %d iterations.\n", j - i);
            }
        }
    }

    return 0;
}
