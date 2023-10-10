/*sizeof() is a function that returns an integer that is 
the size of the array in bytes*/
#include <stdio.h>

int main() 
{
  
  int arr[] = {3, 8, 4, 0, 9};
  printf("%ld\n", sizeof(arr) / sizeof(int));


return 0;

}