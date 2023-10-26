#include<stdio.h> 

void changex(int x);
void callref(int y);

int main(void)
{
    int x = 1;
    changex(x);
    printf("%i\n", x);
    callref(5);
    return 0;
}
void changex(int x)
{
    x = x + 1;
}

//This is call by value!

void callref(int y){
    scanf("%i", &y);
    //int y is the integer
    //&y is the address of the integer
    //int i, *p - is the pointer that points to i
    //it does not store the type!
}

//NULL is an addess, p = NULL
