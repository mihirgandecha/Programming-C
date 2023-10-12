#include <stdio.h>

int main(void) {
/* Step 1: Structures allow for components of different types to be in one single names variable.
    - Component has to be individually DECLARED (not with value yet)! RULE 1!
    - We cannot have repeating type, for instance long id, double id - be careful! RULE 2:
*/
  struct Person { //struct is keyword, Person is a structure tag name, and things like age is members of structure
    char firstName[25];
    char lastName[40];
    int age;
  };
  
  // Step 2: ASSIGN VALUES. Be sure to order in same way as declaration!
  struct Person person1 = {"Ada", "Lovelace", 28};
  struct Person person2 = {"Marie", "Curie", 44}; 
}