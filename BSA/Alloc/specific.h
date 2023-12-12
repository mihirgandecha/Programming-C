#pragma once

#include "../bsa.h"

#define OUTBOUND -1
#define OUTBOUND_END 1073741823
#define MAX_MASTERROW 29
#define SHIFT_ADJUST 2

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
//Checks if index is in bound by calculating its masterRow
bool is_indxinBound(int indx);
//Checks bsa_init and index in bound 
bool indxallocCheck(bsa* b, int indx);

//Helper functions to bsa_set, split by check then performing functionality:
//Second Allocation (after whole bsa struct initalised), allocating Cell Struct
bool check_alocCellStruct(bsa* b, int mRowVal);
bool alloc_CellStruct(bsa* b, int mRowVal);
//Third Allocation - Cell row array calloced according to rowlen
bool check_AllocCellRow(bsa* b, int mRowVal);
bool alloc_CellRow(bsa* b, int mRowVal);
//Final helper, setting value d and signalling its allocation
bool set_value(bsa* b, int indx, int d);
//Helper function for bsa_delete:
bool bsa_Delrow(bsa* b, int mRowVal);
void bsa_DelCell(bsa* b, int currentPosition, int mRowVal);
//Helper for bsa_maxindx - finding X given Y found:
int findX(bsa* b, int rowY);
//Helper function for bsa_free:
bool bsa_freeData(bsa* b, int bsaRow);
void free_inUse(Cell_Row* row);
void free_cellRow(Cell_Row* row);

//Helper functions for bsa_tostring:
void bsa_tostring_row(bsa* b, int bsaRow, char* str);
void bsa_tostring_cell(bsa* b, int bsaRow, int currentPosition, int cellEnd, char* str);

//Calculation Functions:
//Calculates what masterRow given the Index and returns pointer TODO: Remove masterR?
int get_MasterRow(int index);
//Calculates the Cell Row Starting Index given masterRow:
int get_CellRowStart(int mRowVal);
//Calculates the Cell Row Ending Index given masterRow:
int get_CellRowEnd(int index_start);
//Calculates the Cell Row Length given masterRow:
int get_cellLen(int mRowVal);
//Calculates the position within a Cell Array:
int get_CellPos(int indx);

