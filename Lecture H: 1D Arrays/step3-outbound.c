#include <stdio.h>
#define N 50 //GOOD PRACTICE 1: Always hash-define array size
/*Benefits:
    - Consistency (ensure array is always initialised with correct number of elements). Important in large codebase with many arrays
    where it is hard to keep track of all array sizes manually
    - Readability (easy and quick to read if array defined with constant)
    - Error prevention (prevents out of bounds)
    - Performance (sometimes compiler optimises code for hash-defined)
    - Portability (when using different compiler it generates same output)

*/

/*Example 1: Accessing array out of bounds!*/
int main(void) {
int arr[] = {1, 2, 3, 4, 5}; //This is a variable length array - do not use! Very risky behaviour
    
// Print the value of the element at index 3.
printf("arr[3] = %d\n", arr[3]);

 //GOOD PRACTICE 2: EX1 Remedy: USE FIXED LENGTH ARRAY!
 int arr2[5];

// Initialize the array with values. We can do it this way, instead of {}
arr2[0] = 1;
arr2[1] = 2;
arr2[2] = 3;
arr2[3] = 4;
arr2[4] = 5;

// Print the value of the element at index 3.
printf("arr[3] = %d\n", arr[3]);

/*Output:

arr[3] = 4
*/

arr[-1]; //this does not work!
// Loop over the array and print the value of each element.
for (unsigned int i = 0; i < 5; i++) { //GOOD PRACTICE 3! we cannot have -1 as an index! ALWAYS set counter as unsigned!
  printf("arr[%d] = %d\n", i, arr[i]);

/*Outputs: 
arr[0] = 1
arr[1] = 2
arr[2] = 3
arr[3] = 4
arr[4] = 5
*/

  // Access the element at index 5 of the array arr, which is out of bounds.
  arr[10] = 100;

  // Print the value of the unrelated variable.
  printf("Unrelated variable: %d\n", arr[10]);

  return 0;
}





