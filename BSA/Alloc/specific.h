#pragma once

#include "../bsa.h"

#define OUTBOUND -1
#define OUTBOUND_END 1073741823
#define MAX_MASTERROW 29
//renamed variables
typedef struct Cell_Row{
    int* cellRow;
    bool* isD_Allocated; 
    int cellRow_Start;
    int cellRow_End;
    int cellrow_Len; 
    int dAllocSize;
}Cell_Row;

struct bsa {
    Cell_Row* masterRow[BSA_ROWS]; 
};

//Helper function to bsa_init:
bool test_firstInit(bsa *b);

//General Helper Function: Checks bsa_init and index in bound 
bool check_initial_conditions(bsa* b, int indx);

//Helper functions to bsa_set:
bool alloc_CellStruct(bsa* b, int mRowVal);
bool check_alocCellStruct(bsa* b, int mRowVal);
//Third Allocation - rowlen calloced
//Does it need to be allocated?
bool check_AllocCellRow(bsa* b, int mRowVal);
//Allocate Cell Row for rowlen and allocate bool array
bool alloc_CellRow(bsa* b, int mRowVal);

// void asserttest_secondAlloc(void);
void asserttest_ThirdAlloc(void); //TODO: Put in last test()

//test functions
// bool test_alloc3(bsa* b, int masterR);
//Set value d into row
bool set_value(bsa* b, int indx, int d);
//Checking if BSA_Row structure has been allocated space, and 
bool is_ChildRowAloc(bsa* b, int mRowVal);
//Check that the child has been allocated for rowspace


//Helper functions for bsa_tostring:
void bsa_tostring_row(bsa* b, int bsaRow, char* str);
void bsa_tostring_cell(bsa* b, int bsaRow, int currentPosition, char* str);

bool bsa_freeData(bsa* b, int bsaRow);

//General Helper Functions:
//Calculates what masterRow given the Index and returns pointer TODO: Remove masterR?
int get_MasterRow(int index);
void testget_MasterRow(void);
//Calculates the Cell Row Starting Index given masterRow:
int get_CellRowStart(int mRowVal);
void testget_CellRowStart(void);
//Calculates the Cell Row Ending Index given masterRow:
int get_CellRowEnd(int index_start);
void testget_CellRowEnd(void);
//Calculates the Cell Row Length given masterRow:
int get_cellLen(int mRowVal);
void test_int_rowLen(void);
//General Checking Functions:
//Checks if index is in bound by calculating its masterRow
bool is_indxinBound(int indx);
//Testing that masterR is within bounds of 0->29
bool is_MasterinBound(int mRowVal);
void testis_MasterinBound(void);

