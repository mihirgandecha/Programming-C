#include <stdio.h>

int min(int a, int b);

int main(void)
{
    int j, k, m;
    printf("Input two integers: ");
    if(scanf("%i%i", &j, &k) != 2){
        printf("Please input two integers");
        return 1;
    } // Checking user inputs two integers

    m = min(j, k); //Cakkubg the min fnction, storing the value in m
    printf("\nOf the two values %i and %i, " \
    "the minimum is %i. ",j, k, m);

    return 0;
}
int min(int a, int b){

    if (a < b){
        return a;
    }
    else    
        {return b;
        }

}