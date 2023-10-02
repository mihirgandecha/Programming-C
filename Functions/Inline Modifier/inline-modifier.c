#include <stdio.h>

static inline int min(int a, int b);
/*saying to compiler that it should substitute body of 
the function into the code at the point where 
it is called, instead of generating a function call*/

int main(void)
{
    int j, k, m;

    printf("Input two integers: ");
    scanf("%i%i", &j, &k);
    m = min(j, k);
    printf("Minimum is %i\\n", m);

    return 0;
}

inline int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}
