/*CALL BY REFERENCE: LEARN THIS BY HEART!
TAKE HOME THOUGHT: When you are PASSING an array in functions - IT IS NOT COPIED! THE ORIGINAL ARRAY WILL BE MODIFIED! 
    - this means there is no easy way to copy an array, must be cell by cell!
*/

#include <stdio.h>
#include <math.h>
#include <assert.h>
#define MAX 5

void set_array(int a[MAX], unsigned int len, int n);
/*Step 1:
    Function takes an array, and sets all the values to be n
    - We are also passing the length of array (don't need to always because we know the MAX is a constant of 5) - but reasons come later
    - We want to alter len
    - We finally set to be n


*/

int main(void)
{
    int x[MAX] = {2, 3, 3, 3, 3};
    set_array(x, 5, 3); assert(x[4] == 3); //better to do testing in void test(void) - but this does work!
    /*
    Prints:
    x[0] = 5;
    x[1] = 5;
    x[2] = 5;
    x[3] = 5;
    x[4] = 5;
    */
    set_array(x, 5, 4); assert(x[2] == 4);
    set_array(x, 1, 0); assert(x[0] == 0);

    /*
    x[0] = 1;
    x[1] = 2; 
    x[2] = 3;
    */
    set_array(x, 3, 2);
    assert(x[2] == 2); assert(x[3] == 4);

    return 0;
}


void set_array(int a[MAX], unsigned int len, int n)
{
    if (len == 0) //unsigned therefore positive. Step 1: len function calculates how many elements in array, and equates if it is 0 (if empty)
    {
        return; //if 0 elements then return
    }
    for (unsigned int i = 0; i < len; i++) //
    {
        a[i] = n; //the function sets each element to the value of n. i starts at 0, so the first array a[0] is set to n, all the say to the len.
    }
    /*
    General Mihir Q: Here i++ in for loop means that the loop happens first, then i is incremented.
        - if we use for loop to print numbers (int i=0; i < 10; ++i) will print numbers 0-9
        - vice versa (i++) prints 1-10
    */
    /*
    General Mihir Q2. no return as it already modifies the array! Passing array in function - function receives a pointer to the array
        - meaning no need for return */

    /*
    GMihir3: Void is used to indicate that function does not return a value. Very useful for functions that modify program, such as array    
    */
}