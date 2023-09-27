#include <stdio.h>

int main(void)
{
    int n = 9; //COUNTER

    /* This program always prints at least one
       number, even if n is initialised to 0 */
    do{
        printf("%i ",n);
        n--; //INSTRUCTIONS
    }while(n > 0); //TEST

    printf("\n");
    return 0;
}

/*Used in checking user input validation and retry mechanism (retrying operations until it succeeds - Notion)*/