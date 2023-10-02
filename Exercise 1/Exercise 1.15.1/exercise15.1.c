#include <stdio.h>

static inline int hailstone(int a);

int main(void){

    int b;
    printf("Type in the initial number of the Hailstone sequence: ");
    if(scanf("%i", &b) == 0){
        return 1;
    }
    else{
    hailstone(b);
    return 0;
    }
}

int hailstone(int a){
    int i = 1;
    for(i; a != 1; ++i){
        printf("%d ", a);
        if (a % 2 == 0){
            a /= 2;
        }
        else{ 
            a = (3 * a) + 1;
        }
}
printf("1\n");
return a;
}