// #include "arr.h"
// #include "specific.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define COLLTYPE "Realloc"
#define MAXSIZE 1000


typedef struct arr{
    int *a[MAXSIZE];
} arr;

arr init(void);

int main(void){
    arr a = init();
    assert(a != NULL);
    return 0;
}

/* Creates the empty array */
arr init(void){
    arr *a = (arr*)calloc(1, sizeof(int));
    
    return *a;
}
// /* Similar to l[n] = i, safely resizing if required */
// void arr_set(arr *l, int n, int i);
// /* Similar to = l[n] */
// int arr_get(arr *l, int n);
// /* Clears all space used, and sets pointer to NULL */
// void arr_free(arr **l);
