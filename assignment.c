#include <stdio.h>

 int main(void)
 {
	int i = 0;//variable int i = 0
	int power = 1; //variable power = 1

	while (++i <= 10){ //while +1 to i is less than 10, run loop
		printf("%5i", power *= 2); /*The function first assigns power
					     to 2 then makes it equal to power.
					     Then it formats it as "%5i" meaning the
					     value will be printed as a right-justifed intiger
					     with minimum field width of 5. */
	}
	printf("\n");
	return 0;
}

