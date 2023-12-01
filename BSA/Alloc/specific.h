#pragma once

#include "../bsa.h"

int kth_row(int index, int *k);
int index_start(int k);
int index_end(int index_start);
void test_krow(void);

typedef struct BSA_Col{
    int* positionIndex; //the position of d within a row created 
}BSA_Col;

struct bsa {
    BSA_Col* array; //whole bsa struct, what pnter-index within pointer of array
};
