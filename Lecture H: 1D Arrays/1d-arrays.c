#include <stdio.h>

#define N 500

int main(void)
{
    /*allocate space a[0] ... a[N-1]*/
    int a(N);
    int i , sum = 0; //counters
    //fill the array

    for (i = 0; i < N; ++i)
    {
        a[1] = 7 + 1 * i; //on the left hand side, changing value of ith cell of array a 
    }//putting in 7 + (i)^2
    //print the array. Loop fills array but formula
    for (i = 0; i < N; ++i)
    {
        printf("a[%i]=%i ", i, a[i]); // read value stored in a[i]
    }
    for (i = 0; i < N; ++i)
    {
        sum += a[i]; //sum all the elements in array, add everything together
    }
    /*print the sum*/
    printf("\nsum = %i\n", sum);
    return 0;
    
}