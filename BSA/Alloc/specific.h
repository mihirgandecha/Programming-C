#pragma once

#include "../bsa.h"

int kth_row(int index, int *k);
int index_start(int k);
int index_end(int index_start);
void test_krow(void);
void testIstart(void);
void testIend(void);

typedef struct BSA_Col{
    int* positionIndex; //the position of d within a row created 
}BSA_Col;

struct bsa { //whole bsa structure
    BSA_Col* array; //1D array of pointers
};

// typedef struct indxFigures{
//     int kthRow;
//     int kStart;
//     int kEnd;
//     int rowLen;
// }indxFigures;
