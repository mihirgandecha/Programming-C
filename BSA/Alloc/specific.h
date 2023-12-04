#pragma once

#include "../bsa.h"

#define OUTBOUND -1
#define MAXSTART_INDEX 536870911
#define MAXEND_INDEX 1073741822
#define OUTBOUND_END 1073741823

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

bool storeData(bsa* b, int k);
// bool bsa_set2(bsa* b, int indx, int d);

int kth_row(int index, int *k);
int index_start(int k);
int index_end(int index_start);
void test_krow(void);
void testIstart(void);
void testIend(void);

//testing k
bool testK(int k);
void test_testK(void);

//new k:
// void kthRow_Helper(int indx, int *k);
// int kthRow_Main(int indx);
// void test_krowNew(void);
