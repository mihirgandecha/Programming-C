/* Structures like arrays hold lots of memory. We need to manage this memory!
    USE POINTERS! Variable that holds the memory address to another variable.
*/

#include <stdio.h>

struct Person {
  char name[40];
  int age;
};

int main(void) {
  struct Person person1 = {"Martin", 57};
  struct Person person2 = {"Michelle", 27};
  // STEP1: Define the structure variable:
  struct Person* person1Pointer = &person1;
  struct Person* person2Pointer = &person2;

   //We can access member variable using following:
  (*person1Pointer).age += 1;
   //However easier way is like below: 
  person2Pointer->age+=10;

  printf("Hello my name is %s and I am %d years old.\n", person1.name, person1.age);
  printf("Hello my name is %s and I am %d years old.\n", person2.name, person2.age);
}