#include <stdio.h>
#include <math.h> //When doing powers, as it cannot be written as '^', uses pow() function and therefore needs this

int main(void)
{
    /* +, -, /, *, %
    Addition, Subtraction (use hyphen key), Division, Multiplication, Modulus.
    Integer arithmetic discards remainer. i.e. 1/2 is 0, 7/2 is 3.
    Modulus gets the remainder, i.e. 7%2 is 1.
    */

   //ADDITION

   int a;

   a = 5 + 4;

   printf("a is equal to %i\n", a); 

   //SUBRACTION

   int b;

   b = 15 - 3 - 6 - 20; //can go to negatives but won't do decimal unless type is defined

   printf("b is equal to %i\n", b); 

   //DIVISION

   int c;

   c = 9 / 4; //note that 2 prints out as remainer is discarded

   printf("c is equal to %i\n", c); 


   //MULTIPLICATION

   int d;

   d = 5 * 50 * 2; //note can have multiple equations, i.e. prints 500

   printf("d is equal to %i\n", d); 

   //MODULUS

   int e;

   e = 10 % 3; //3*3=9 remainder 1 is 10 so outputs 1

   printf("e is equal to %i\n", e); 
   
   //EXPERIMENTAL

   int f;

   f = (12%5) * 10; //Operations inside () are done first.
   
   printf("f is equal to %i\n", f);  

   //POWERS:
   int g;

   g = pow(6, 2); //Calculated 6 to the power of 2

   printf("g is equal to %i\n", g); 

   //DECIMALS

   double h;

   h = (double)10 / 4; // need to define that you are expecting a double

   printf("h is equal to %e\n", h); 

   //DIVIDING DECIMALS

   double i;

   i = (double)10 / 4; // need to define that you are expecting a double

   printf("i is equal to %1f\n", i); 

   //EXACT DECIMAL PLACES
   double number = 2.5000;
   printf("Using %%g: %.2g\n", number);  // Output: 2.5
   printf("Using %%f: %.2f\n", number);  // Output: 2.50


   return 0;
}