#include <stdio.h>

int main(void){

    int a;
    printf("Please enter one short int: ");
    if(scanf("%hd", &a) == 0){
        return 1;
    }
    else{
        printf("%hd\n", a);
        printf("Short Int: %3li\n", sizeof(short));
    }

    int b;
    printf("Please enter one unsigned short int: ");
    if(scanf("%hu", &b) == 0){
        return 1;
    }
    else{
        printf("%hu\n", b);
        printf("Unsigned Short Int: %3li\n", sizeof(unsigned));
    }
    return 0;
}