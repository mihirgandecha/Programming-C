#pragma once

#include "../bsa.h"

#define OUTBOUND -1
#define OUTBOUND_END 1073741823
#define MAX_MASTERROW 29
//renamed variables
typedef struct Cell_Row{
    int* cellRow;
    bool* inUse; 
    int start;
    int end;
    int length; 
    int size;
}Cell_Row;

struct bsa {
    Cell_Row* masterRow[BSA_ROWS]; 
};

//Helper function to bsa_init:
bool test_firstInit(bsa *b);

//Helper functions to bsa_set, split by check then performing functionality:
//Second Allocation (after whole bsa struct initalised), allocating Cell Struct
bool check_alocCellStruct(bsa* b, int mRowVal);
bool alloc_CellStruct(bsa* b, int mRowVal);
//Third Allocation - Cell row array calloced according to rowlen
bool check_AllocCellRow(bsa* b, int mRowVal);
bool alloc_CellRow(bsa* b, int mRowVal);
//Final helper, setting value d and signalling its allocation
bool set_value(bsa* b, int indx, int d);

//Helper functions for bsa_tostring:
void bsa_tostring_row(bsa* b, int bsaRow, char* str);
void bsa_tostring_cell(bsa* b, int bsaRow, int currentPosition, int cellEnd, char* str);

bool bsa_freeData(bsa* b, int bsaRow);

//Helper function for bsa_delete:
void delete_helper(bsa* b, int currentPosition, int mRowVal);

//Helper function for bsa_free:
bool bsa_freerow(bsa* b, int mRowVal);

//Calculation Functions:
//Calculates what masterRow given the Index and returns pointer TODO: Remove masterR?
int get_MasterRow(int index);
void testget_MasterRow(void);
//Calculates the Cell Row Starting Index given masterRow:
int get_CellRowStart(int mRowVal);
//Calculates the Cell Row Ending Index given masterRow:
int get_CellRowEnd(int index_start);
void testget_CellRowEnd(void);
//Calculates the Cell Row Length given masterRow:
int get_cellLen(int mRowVal);
void test_int_rowLen(void);

//Checking Helper Function: 
//Checks bsa_init and index in bound 
bool indxallocCheck(bsa* b, int indx);
//Checks if index is in bound by calculating its masterRow
bool is_indxinBound(int indx);

void free_inUse(Cell_Row* row);
void free_cellRow(Cell_Row* row);
