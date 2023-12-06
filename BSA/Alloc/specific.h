#pragma once

#include "../bsa.h"

#define OUTBOUND -1
#define OUTBOUND_END 1073741823
#define EMPTY 0

//typedef operations function?!can these test can only be for MasterRow?!!!
typedef struct bsaOperations{
    bool (*test_firstInit)(struct bsa*); //testing if 1 space created for b and ops & each has been set to 0!
}bsaOperations;

typedef struct BSA_Row{
    int* child; //the position of d within a row created
    int kStart;
    int kEnd;
    int rowLen; 
}BSA_Row;

struct bsa { //whole bsa structure
    BSA_Row* master[BSA_ROWS]; //1D array of pointers - change to just array of 30
    bsaOperations* ops;
};

//test if a bsa has been initialised, returning false if NULL 
bool test_firstInit(bsa *b);
//test and store the result of test_firstInit into structure
bsa* initialiseOp1(void);

// bool storeData(bsa* b, int k);
bool allocateChild(bsa* b, int k, int rowLen);
//Checking if BSA_Row structure has been allocated space, and 
bool is_ChildAloocated(bsa* b, int k);
//Check that the child has been allocated for rowspace
bool isRowEmpty(bsa* b, int k, int rowLen);
//Storing data into structure
void storeData(bsa* b, int k, int rowLen);
// bool bsa_set2(bsa* b, int indx, int d);
int find_masterrow(int k, int indx);

int kth_row(int index, int *k);
void test_kRow(void);

int index_start(int k);
void testIstart(void);

int index_end(int index_start);
void testIend(void);

//testing given k, generates a row len of 2^k
int row_len(int k);
void test_int_rowLen(void);

//Testing that k is within bounds of 0->29
bool testK(int k);
void test_testK(void);

// bool is_indxInbound(int index, int rowStart, int rowEnd);
// void test_is_indxInbound(void);
//new k:
// void kthRow_Helper(int indx, int *k);
// int kthRow_Main(int indx);
// void test_krowNew(void);
