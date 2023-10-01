#include <stdio.h>

int min(int a, int b); //function top line - declaring a function called min

int main(void) //like a title of book
{
    int j, k, m;

    printf("Input two integers: ");
    scanf("%i%i", &j, &k); //check a return value - if statement
    m = min(j, k); //pass functions at top
    printf("\nOf the two values %i and %i, the minimum is %i.\n\n", j, k, m);

    return 0; //can you leave function main
}

int min(int a, int b) //
{
    if (a < b) //these are unbraced!!!
        return a;
    else
        return b;
}//What if this had a scanf input statement? What would happen?

/*inside main is set of variables of j,k. min knows nothing about j and k.
Makes no difference */
