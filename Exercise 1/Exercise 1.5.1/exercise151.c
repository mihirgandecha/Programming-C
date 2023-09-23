#include <stdio.h>

/*TIP: All about precedence. ++ first, = has lowest precedence, 
and a right to left assicuativity. 
SCAN LEFT TO RIGHT AND FIND THE ++, do that first. */

/* For instance, a = b = c = 0; is equivalent to:
   a = (b = (c = 0))

   + is left-to-right. 1 + 2 + 3 is the same as:
     (1 + 2) + 3

     In this exercise as + is a higher precendence, we do this first.
*/


int main(void) 
{
  int a, b = 0, c = 0;

  printf("a = %d, b = %d, c = %d\n", a, b, c); // prints a = RANDOM, b = 0, c = 0

  //EXAPLE 1:
  a = ++b + ++c;
  printf("a = %d, b = %d, c = %d\n", a, b, c); // prints a = 2, b = 1, c = 1
  /* Pre-increment operator (DO IT NOW). Meaning ++ function FIRST. Therefore b ++ is b=1. THEN c = 1. 
  THEN a = b + c which means a = 2 */


  printf("We are currently on a = %d, b = %d, c = %d\n", a, b, c); // prints a = 2, b = 1, c = 1

  //EXAPLE 2:
  a = b++ + c++;
  printf("a = %d, b = %d, c = %d\n", a, b, c); // prints a = 0, b = 1, c = 2
  /* Post-increment operators (HOLD IT OFF). Essentially post is saying use the current values of b and c (1).
   Then a = 1+1 which is 2. Then post-increment means operation happens after meaning b && c = 2 */

  printf("We are now on a = %d, b = %d, c = %d\n", a, b, c); // prints a = 2, b = 2, c = 2

  //EXAPLE 3:
  a = ++b + c++;
  printf("a = %d, b = %d, c = %d\n", a, b, c); // prints a = 5, b = 3, c = 3
  /*Here we have a pre and post-increment operator. Originally ALL = 2. pre-increment of b happens first
  meaning b = 3. THEN c post-incrememnt means hold it off - a = 3+2 meaning a = 5. FINALLY c = 3*/

  printf("Finally, we are now on a = %d, b = %d, c = %d\n", a, b, c); // prints a = -2, b = 2, c = 3

  //EXAMPLE 4:
  a = b-- + --c; //make sure to use (-) instead of the MINUS sign (-)!!!
  printf("a = %d, b = %d, c = %d\n", a, b, c); // prints a = 5, b = 2, c = 2

  return 0;
}
