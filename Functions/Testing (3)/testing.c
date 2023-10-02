//Program that calls the number of factors in a given number

#include <stdio.h>

int numfactors(int f); //saying that there will be a function called numfactors

int main(void)
{
    int n = 12; //int n = numfactors(n)
//or int m = numfactors(n)
    int f = numfactors(n);
    printf("Number of factors in %i is %i\n", n, f); //don't have to do this
    return 0;
}

int numfactors(int k)
{
    int count = 0;
    for (int i = 1; i <= k; i++) //looping 1-12
    {
        if ((k % i) == 0) //bad way
        {
            count++;
        }
    }//if 1/12 THEN counter 1
    return count;
}
//simple way of explaining POINT
//i starts at 1