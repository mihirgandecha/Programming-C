/*Takes one integer as an input and
does not return a value. Void is a type which does not
return a value*/

/*The function fnc1() can be used to perform any task 
that does not require returning a value. 
For example, it could be used to print a message to the console, 
modify a global variable, or call another function.*/
#include <stdio.h>

void fnc1(int x);

int main(void)
{
    int x = 1;

    fnc1(x);
    printf("%i\n", x);


}

void fnc1(int x)
{
    x = x + 1; //why does it print 1 and not 2?
}