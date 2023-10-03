#include <stdio.h>

int main(void){

    float d = 0.1;

    printf("%.12f\n", d);

    if (d == 0.3){
        printf("No\n");
    }
    else{
        printf("Yes\n");
    }

    return 0;
}