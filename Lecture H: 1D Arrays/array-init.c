//Slide 2: Array Initialisation

#include <stdio.h>

/*Step 1: Default arrays are uninitialised,
          Means that we have to assign a value!
          Full of garbage!  
*/
/*Syntax of Array Init:

data_type array_name [size] = {value1, value2, ... valueN};

Example:
*/
int main(void){
float x[7] = {-1.1, 0.2, 2.0, 4.4, 6.5, 0.0, 7.7};
//Float x is initialised with 7 elements

float y[7] = {-1.1, 0.1};
/*Here float x has 2 elements, and now rest of elements are
  set to 0*/

printf("%i\n", y[]);

return 0;
}