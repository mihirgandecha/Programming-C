#include <stdio.h>
struct Person ageOne(struct Person friend1, struct Person* friend2Pointer);


int main(void) {

struct Person {
  char name[40];
  int age;
};

  struct Person myFriend = {"Martin", 57};
  struct Person myOtherFriend = {"Michelle", 27};
  // Call your function below
  myFriend = ageOne(myFriend, &myOtherFriend);
  

  printf("Hello my name is %s and I am %d years old.\n", myFriend.name, myFriend.age);
  printf("Hello my name is %s and I am %d years old.\n", myOtherFriend.name, myOtherFriend.age);
}


// Write your function below
struct Person ageOne(struct Person friend1, struct Person* friend2Pointer){
  friend1.age += 1;
  friend2Pointer -> age += 1;

return friend1;
}

