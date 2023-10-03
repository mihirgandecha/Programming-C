#include <stdio.h>

int main(void){

char c;

c = 'A';
//or:
char c1 = 'A', c2 = '*', c3 = ';';
char d = 'a';

printf("%c\n", c);
printf("%c\n", c1);
printf("%c\n", c2);
printf("%c\n\n", c3);

printf("%c\n", d);
printf("%i\n", d); //prints 97 which is ASCII value
return 0;
}