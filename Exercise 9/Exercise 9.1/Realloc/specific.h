//remove after
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define COLLTYPE "Realloc"
#define MAXSIZE 1000


typedef struct arr{
    int *a[MAXSIZE];
} arr;

arr init(void);