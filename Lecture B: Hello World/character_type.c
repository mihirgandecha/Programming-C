#include <stdio.h> //# is a directive (tool that processes your code before it gets compiled)
#define PI 3.14159265358979

#include "hello_mihir" //since local file use ""

int main(void)
{
   char c; //char stands for character
   
   c = 'A'; //wrap around '' single quotes
   printf("%c ", c); //note different to %i as we are returning a character
   printf("%c\n", c+1);

   printf("%f\n", PI);

   printf("%s\n", myMessage); //including a message from txt file
   return 0;
}