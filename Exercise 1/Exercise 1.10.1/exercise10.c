#include <stdio.h>
//STEP 1
#define A 0
#define C 0
#define M 0
#define SEED 0

int main(void){

//STEP 2: Determine the period (number of iterations it takes for sequence to start repeating itself):

int new_A += A; 
int new_C += C;
int new_M += M;

printf("What numbers would you like to input into the LCG loop? A =  C =  M =  ");
scanf("%i%i%i", &new_A, &new_C, &new_M);

//WHEN CONTINUE INITIALISE FOR LOOP AND PUT IF STATEMENT!

    for(i = 0; i < 10; i++){
        seed = (A * seed + C) % M; //sequence length MAX is same as M


int current_seed = SEED,
int period = 0;
int initial, current;

initial = (A * current_seed + C) % M;
current = initial;






    for(i = 0; i < 10; i++){
        seed = (A * seed + C) % M; //sequence length MAX is same as M

    printf("%i\n", seed);
    }


    return 0;
}