#include <stdio.h>
#define N 5

int main(void)
{
/*General rule 1: We can manipulate certain elements
    - meaning if we stored 6 elements in arr{}
    - arr[4] will look at 10 - starts at 0!

    What about if we want to change the 12?
    - if we change so that the 12 is affected, we need to 
    input another element otherwise we get error:
    *** stack smashing detected ***
    meaning we get an error as we are trying to access 
    elements beyond array*/
  int arr[] = {2, 4, 6, 8, 10, 12, 14};
  arr[6] = arr[N] + 1;
  printf("Rule 1 Result: \n");
  printf("arr[N] = %i\n", arr[6]);

//IMPORTANT! Always think n-1! Arr elements start at 0!!!

/*RULE 2: We can increment the value of element*/
int arr2[] = {3, 6, 9, 12};
arr2[3]++; //manipulating the 12 to give 13
printf("\nRule 2 Result: \n");
printf("arr[4] = %i\n", arr2[3]);

/*RULE 3: Use n[X+counter]=0 to:
    - initialise an array
    - clear an array
    - set individual elements of an array to 0*/

//Initialise:
int n[N];
for (int i = 0; i < N; i++)
{
    n[12 + i] = 0;
    printf("n[%i] = %i\n", i, n[i]);
}
//Outputs 

return 0;
}