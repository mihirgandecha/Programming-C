#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("Randomly distributed integers are printed.\n"
	       "How many do you want to see?	");

	int n;
	if(scanf("%i", &n) == 1){
	   for (int i = 0; i < n; ++1) {
		if (i 
