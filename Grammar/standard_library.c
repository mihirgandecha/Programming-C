#include <stdio.h> //can you get conflict in these functions?
#include <stdlib.h> //allows rand function

int main(void)
{
	printf("Randomly distributed integers are printed.\n"
	       "How many do you want to see?	");

	int n;
	if(scanf("%i", &n) == 1){ //checking to see if 1 number has inputed. IF FAIL THEN GO TO NEXT LINE (return 0)
	   for (int i = 0; i < n; ++i) { //while loop similar as counter is extremely used! int i = 0; TEST (i < n); THEN ++1. FOR SAYS "If all is true, then carry out instructions"
		if (i % 4 == 0){ // The amount of numbers inside i / 4 = 0 THEN Every 4th loop print a new line 
			printf("\n");
		}
	   }
	   printf("%12i", rand()); //DO Print and doing rand first, in a box of 12 spaces
	}
	printf("\n");
	return 0; //done all the printing

}
return 1; // IF the IF LOOP fails, then it goes to return 1, something has gone wrong!



//FOR IS an iteration of while loops. HOWEVER - ++i is done at the end, even though its at the top.