//Slide 2: Array Initialisation

#include <stdio.h>
#define N 5

/*Step 1: Initialisation is the process to assign some
          initial value to the variable
          Default arrays are uninitialised,
          Means that we have to assign a value!
          Full of garbage!  
*/
/*Method 1: Syntax of Array Init Via declaration:
We initialise array along with its declaration
data_type array_name [size] = {value1, value2, ... valueN};

Example:
*/
int main(void){
float x[7] = {-1.1, 0.2, 2.0, 4.4, 6.5, 0.0, 7.7};
//Float x is initialised with 7 elements

float y[7] = {-1.1, 0.1};
/*Here float x has 2 elements, and now rest of elements are
  set to 0*/

printf("%f\n", y[0]);

/*Method 2 of init: We can initialise declaring size of array!
Compiler assumes array is length 4*/
int a[] = {3, 8, 9, 1}; 
a[5] = a[4] + 1;

printf("%i\n", a[5]);

/*Method 3 of init: Array Init after Declaration
  Using LOOPS.
  Use this method to assign initial value to each element*/

  int array_name[N];
  for (int i = 0; i < N; i++) 
  {
    array_name [i] = i * 2;
    printf("array_name[%i] = %i\n", i, array_name[i]);
  }



return 0;
}