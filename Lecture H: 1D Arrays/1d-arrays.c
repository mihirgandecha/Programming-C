#include <stdio.h>
#include <assert.h>

#define N 500

int main(void)
{
    /*allocate space a[0] ... a[N-1]*/
    int a[N]; //Step 1. Creating uninitialised array int type of N array size
    int i , sum = 0; //Step 2. Counter for i and sum
    
    /*Step 3. For loop that changes nth value of array
    For instance, when i = 0, a[1] = 8*/  
    for (i = 0; i < N; ++i)
    {
        a[i] = 7 + i * i; 
    }
    int first = a[1];
    assert(first == 8);
    /*Step 4. Another For loop that prints the counter and array element in nth value of
    array*/
    for (i = 0; i < N; ++i) 
    {
        printf("a[%i] = %i ", i, a[i]); // Outputs a[1] = 8, to 499
    }
    /*Step 5. Sums all the elements in array, add everything together */
    for (i = 0; i < N; ++i)
    {
        sum += a[i]; 
    }
    /*Step 6. Print the sum*/
    printf("\nsum = %i\n", sum);
    return 0;
    
}