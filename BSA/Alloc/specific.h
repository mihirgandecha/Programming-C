#pragma once

#include "../bsa.h"

#define OUTBOUND -1

typedef struct BSA_Col{
    int* positionIndex; //the position of d within a row created
    int kthRow;
    int kStart;
    int kEnd;
    int rowLen; 
    int d;
}BSA_Col;

struct bsa { //whole bsa structure
    BSA_Col* array; //1D array of pointers
};

//test if a bsa has been initialised, returning false if NULL 
bool testInitialisation(bsa *b);
void testInit(void);

int kth_row(int index, int *k);
int index_start(int k);
int index_end(int index_start);
void test_krow(void);
void testIstart(void);
void testIend(void);

//new k:
void kthRow_Helper(int indx, int *k);
int kthRow_Main(int indx);
void test_krowNew(void);
