#include "specific.h"

bsa* bsa_init(void){
    bsa* emptyBSA;
    //Allocate memory for 1 whole bsa structure
    emptyBSA = (bsa*) calloc(1, sizeof(bsa)); 
    if (emptyBSA == NULL){
        return NULL;
    }
    //Set pArray 0-29 to NULL
    for (int bsaRow = 0; bsaRow < BSA_ROWS; bsaRow++){
        emptyBSA->masterRow[bsaRow] = NULL;
    }
    test_firstInit(emptyBSA);
    return emptyBSA;
}

bool test_firstInit(bsa *b){
    if (b == NULL){  
        return false;
    }
    for (int bsaRow = 0; bsaRow < BSA_ROWS; bsaRow++){
        if (b->masterRow[bsaRow] != NULL){
            return false;
        }
    }
    return true;
}

bool is_indxinBound(int indx){
    if ((indx >= OUTBOUND_END) || (indx <= OUTBOUND)){
        return false;
    }
    return true;
}

bool bsa_set(bsa* b, int indx, int d){
    if (!indxallocCheck(b, indx)){
        return false;
    }
    int mRowVal = get_MasterRow(indx);
    bool isRowAlloc = check_AllocCellRow(b, mRowVal);
    bool isStructAlloc = check_alocCellStruct(b, mRowVal);
    if (!isStructAlloc || !isRowAlloc){
        return false;
    }
    return set_value(b, indx, d);
}

bool indxallocCheck(bsa* b, int indx){
    bool isBSAInit = b != NULL;
    bool isMasterInit = isBSAInit && b->masterRow != NULL;
    bool isIndxbound = is_indxinBound(indx);
    bool checkInit = isMasterInit && isIndxbound;

    return checkInit;
}

bool check_AllocCellRow(bsa* b, int mRowVal) {
    if (b->masterRow[mRowVal] == NULL){
        return alloc_CellStruct(b, mRowVal);
    }
    return true;
}

bool alloc_CellStruct(bsa* b, int mRowVal){
    if (b->masterRow[mRowVal] == NULL){ 
        b->masterRow[mRowVal] = (Cell_Row*)calloc(1, sizeof(Cell_Row));
        if (b->masterRow[mRowVal] == NULL){
            return false;
        }
    }
    return true;
}

bool check_alocCellStruct(bsa* b, int mRowVal){
    bool MasterInit = b->masterRow[mRowVal] != NULL;
    bool CellInit = b->masterRow[mRowVal]->cellRow == NULL;
    if (MasterInit && CellInit){
        return alloc_CellRow(b, mRowVal);
    }
    return b->masterRow[mRowVal] != NULL;
}

bool alloc_CellRow(bsa* b, int mRowVal){
    int rowLen = get_cellLen(mRowVal);
    if (b->masterRow[mRowVal]->cellRow == NULL){
        //Allocating memory for the cellRow array
        b->masterRow[mRowVal]->cellRow = (int*)calloc(rowLen, sizeof(int));
        if (b->masterRow[mRowVal]->cellRow == NULL){
            return false;
        }
        //Allocating memory for the bool inUse array
        b->masterRow[mRowVal]->inUse = (bool*)calloc(rowLen, sizeof(bool));
        if (b->masterRow[mRowVal]->inUse == NULL){ 
            return false;
        }
        for (int rowX = 0; rowX < rowLen; rowX++){
            b->masterRow[mRowVal]->inUse[rowX] = false;
        }
    } 
    return true;
}

bool set_value(bsa* b, int indx, int d) {
    int mRowVal = get_MasterRow(indx);
    b->masterRow[mRowVal]->start = get_CellRowStart(mRowVal);
    b->masterRow[mRowVal]->end = get_CellRowEnd(mRowVal);
    b->masterRow[mRowVal]->length = get_cellLen(mRowVal);
    int position = get_CellPos(indx);;
    if (position < 0 || position > b->masterRow[mRowVal]->end){
        return false;
    }
    b->masterRow[mRowVal]->cellRow[position] = d;
    b->masterRow[mRowVal]->inUse[position] = true;
    b->masterRow[mRowVal]->size += 1;
    return true;
}

int get_MasterRow(int index){
    for (int mRowVal = 0; mRowVal < BSA_ROWS; mRowVal++){
        int cellRowStart = get_CellRowStart(mRowVal);
        int cellRowEnd = get_CellRowEnd(mRowVal);
        if ((index >= cellRowStart) && (index <= cellRowEnd)){
            return mRowVal;
        }
    }
    return OUTBOUND;
}

int get_cellLen(int mRowVal){
    if (mRowVal == 0){
        return 1;
    }
    return (1L << mRowVal);
}

int get_CellRowStart(int mRowVal){
    if (mRowVal == 0){
        return 0;
    }
    return (1L << mRowVal) - 1;
}

int get_CellRowEnd(int mRowVal){
    if (mRowVal == 0){
        return 0;
    } 
    return (1L << (mRowVal + 1)) - SHIFT_ADJUST;
}

int get_CellPos(int indx){
    int mRowVal = get_MasterRow(indx);
    int base = (1L << mRowVal) - 1;
    if (indx < base) {
        return OUTBOUND;
    }
    return indx - base;
}

int* bsa_get(bsa* b, int indx){
    if (!indxallocCheck(b, indx)){
        return NULL;
    }
    int mRowVal = get_MasterRow(indx);
    if (!b->masterRow[mRowVal] || !b->masterRow[mRowVal]->cellRow){
        return NULL;
    }
    int position = get_CellPos(indx);;
    int cellLen = b->masterRow[mRowVal]->length;
    if (position < 0 || position >= cellLen){
        return NULL;
    }
    return &(b->masterRow[mRowVal]->cellRow[position]);
}

bool bsa_delete(bsa* b, int indx){
    int mRowVal = get_MasterRow(indx);
    int position = get_CellPos(indx);
    if (!indxallocCheck(b, indx) || !b->masterRow[mRowVal]->inUse[position]){
        return false;
    }
    if (b->masterRow[mRowVal]->size == 1){
        if(!bsa_Delrow(b, mRowVal)){
            return false;
        }
        return true;
    }
    if (b->masterRow[mRowVal]->size > 1){
        bsa_DelCell(b, position, mRowVal);
        return true;
    }
    return false;
}

bool bsa_Delrow(bsa* b, int mRowVal){
    if(b->masterRow[mRowVal]->cellRow != NULL){
        free(b->masterRow[mRowVal]->cellRow);
        b->masterRow[mRowVal]->cellRow = NULL;
        free(b->masterRow[mRowVal]->inUse);
        b->masterRow[mRowVal]->inUse = NULL;
        free(b->masterRow[mRowVal]);
        b->masterRow[mRowVal] = NULL;
        return true;
    }
    return false;
}

void bsa_DelCell(bsa* b, int currentPosition, int mRowVal){
    b->masterRow[mRowVal]->cellRow[currentPosition] = 0;
    b->masterRow[mRowVal]->inUse[currentPosition] = false;
    b->masterRow[mRowVal]->size -= 1;
}

int bsa_maxindex(bsa* b){
    if (!b || !b->masterRow){
        return OUTBOUND;
    }
    for (int rowY = MAX_MASTERROW; rowY >= 0; rowY--){
        if (b->masterRow[rowY] != NULL){ 
            int lastUsedCell = findX(b, rowY);
            if (lastUsedCell != OUTBOUND){
                return lastUsedCell;
            }
        }
    }
    return OUTBOUND;
}

int findX(bsa* b, int rowY){
    int cellStart = b->masterRow[rowY]->start;
    int rowXMax = b->masterRow[rowY]->end;
    for(int rowX = rowXMax; rowX >= cellStart; rowX--){
        if(b->masterRow[rowY]->inUse[rowX - cellStart]){
            return rowX;
        }
    }
    return OUTBOUND;
}

bool bsa_free(bsa* b){
    if (b == NULL){
        return false;
    }
    for (int mRowVal = 0; mRowVal < BSA_ROWS; mRowVal++){
        if (b->masterRow[mRowVal] != NULL){
            free_cellRow(b->masterRow[mRowVal]);
            free_inUse(b->masterRow[mRowVal]);
            free(b->masterRow[mRowVal]);
            b->masterRow[mRowVal] = NULL;
        }
    }
    free(b);
    return true;
}

void free_cellRow(Cell_Row* row){
    if (row->cellRow != NULL){
        free(row->cellRow);
        row->cellRow = NULL;
    }
}

void free_inUse(Cell_Row* row){
    if (row->inUse != NULL){
        free(row->inUse);
        row->inUse = NULL;
    }
}

bool bsa_tostring(bsa* b, char* str){
    if ((b == NULL) || (str == NULL)){
        return false;
    }
    int maxIndex = bsa_maxindex(b);
    if (maxIndex == OUTBOUND){
        strcpy(str, "");
        return true;
    }
    str[0] = '\0';
    int mRowVal = get_MasterRow(maxIndex);
    for (int bsaRow = 0; bsaRow <= mRowVal; bsaRow++){
        bsa_tostring_row(b, bsaRow, str);
    }
    return true;
}

void bsa_tostring_row(bsa* b, int bsaRow, char* str){
    if (b->masterRow[bsaRow] == NULL){
        strcat(str, "{}");
    }
    else{
        int cellStart = b->masterRow[bsaRow]->start;
        int cellEnd = b->masterRow[bsaRow]->end; 
        strcat(str, "{");
        for(int rowX = cellStart; rowX <= cellEnd; rowX++){
            bsa_tostring_cell(b, bsaRow, rowX, cellEnd, str);
        }
        strcat(str, "}");
    }
}

void bsa_tostring_cell(bsa* b, int bsaRow, int currentPosition, int cellEnd, char* str){
    int cellPos = get_CellPos(currentPosition);
    int nextCell = cellPos + 1;
    if(b->masterRow[bsaRow]->inUse[cellPos] == true){
        char temp[1000]; 
        int d = b->masterRow[bsaRow]->cellRow[cellPos];
        sprintf(temp, "[%d]=%d", currentPosition, d);
        strcat(str, temp);
        if (currentPosition != cellEnd && b->masterRow[bsaRow]->inUse[nextCell] == true){
            strcat(str, " ");
        }
    }
}

void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc){
    int max_index = bsa_maxindex(b);
    for (int rowX = 0; rowX <= max_index; rowX++){
        int* pCell = bsa_get(b, rowX);
        if (pCell != NULL){
            func(pCell, acc);
        }
    }
}

void test(void){
    //Test for index is in bound:
    assert(!is_indxinBound(OUTBOUND));
    assert(is_indxinBound(3));

    //Test for finding Value in Master Row given index:
    assert(get_MasterRow(0) == 0);
    assert(get_MasterRow(1) == 1);
    assert(get_MasterRow(14) == 3);
    assert(get_MasterRow(30) == 4); 
    assert(get_MasterRow(128) == 7);

    //Cell Length Tests:
    assert(get_cellLen(0) == 1);
    assert(get_cellLen(1) == 2);
    assert(get_cellLen(2) == 4);
    assert(get_cellLen(3) == 8);

    //Test Cell Row Starting Index:
    assert(get_CellRowStart(4) == 15);
    assert(get_CellRowStart(5) == 31);
    assert(get_CellRowStart(6) == 63);
    assert(get_CellRowStart(BSA_ROWS - 1) == 536870911); //last row 29

    //Test Cell Row Ending Index:
    assert(get_CellRowEnd(4) == 30);
    assert(get_CellRowEnd(5) == 62);
    assert(get_CellRowEnd(6) == 126);
    assert(get_CellRowEnd(BSA_ROWS - 1) == 1073741822); //last row 29

    //Test generate position given indx:
    assert(get_CellPos(7) == 0);
    assert(get_CellPos(15) == 0);
    assert(get_CellPos(16) == 1);
    assert(get_CellPos(31) == 0);
    //Testing by comparing that results of testBsa (each function passed) == testcompareBSA
    //Testing Function 1: bsa_init:
    bsa* testBsa = bsa_init();
    assert(test_firstInit(testBsa));
    bsa* testcompareBSA = bsa_init();
    assert(test_firstInit(testcompareBSA));
    //bsa_set helper functions assert tests:
    int indx = 7;
    int mRowVal = get_MasterRow(indx);
    assert(mRowVal == 3);
    int d = 50;
    bsa_set(testcompareBSA, indx, d);
    assert(testcompareBSA->masterRow[mRowVal]->cellRow[0] == 50); //TODO: Func for getting index pos in cellRow?
    assert(testcompareBSA->masterRow[mRowVal]->inUse[0] == true);
    assert(testcompareBSA->masterRow[mRowVal]->size == 1);
    bsa_set(testcompareBSA, 8, 101);
    assert(testcompareBSA->masterRow[mRowVal]->size == 2);
    bsa_delete(testcompareBSA, 7);
    assert(testcompareBSA->masterRow[mRowVal]->size == 1);
    //Check second allocation:
    assert(indxallocCheck(testBsa, indx) == true);
    check_AllocCellRow(testBsa, mRowVal);
    alloc_CellStruct(testBsa, mRowVal);
    assert(testBsa->masterRow[mRowVal] != NULL);
    //Third allocation test
    check_alocCellStruct(testBsa, mRowVal);
    alloc_CellRow(testBsa, mRowVal);
    int rowLen = get_cellLen(mRowVal);
    for (int rowX = 0; rowX < rowLen; rowX++){
        assert(testBsa->masterRow[mRowVal]->cellRow[rowX] == 0);
        assert(testBsa->masterRow[mRowVal]->inUse[rowX] == false);
    }
    set_value(testBsa, indx, d);    
    assert(testBsa->masterRow[mRowVal]->inUse[0] == true);
    assert(testBsa->masterRow[mRowVal]->cellRow[0] == 50);

    // Testing Function 3: bsa_get:
    int* p = bsa_get(testBsa, 7);
    assert(*p == 50);

    // Testing Function 4: bsa_delete (delete one cell):
    bsa_set(testBsa, 8, 60);
    int pos = get_CellPos(8);
    assert(pos == 1);
    int mRow4 = get_MasterRow(8);
    assert(mRow4 == 3);
    bsa_DelCell(testBsa, pos, mRow4);
    assert(testBsa->masterRow[mRow4]->inUse[pos] == false);
    assert(testBsa->masterRow[mRow4]->size == 1);

    // Testing Function 4: bsa_delete (delete row):
    bsa_Delrow(testBsa, mRow4);
    assert(!testBsa->masterRow[mRowVal]);

    // Testing Function 6: free_cellRow:
    bsa_set(testBsa, 10, 20);
    bsa_set(testBsa, 11, 22);
    free_cellRow(testBsa->masterRow[mRowVal]);
    assert(!testBsa->masterRow[mRowVal]->cellRow);

    // Testing Function 7: free_inUse:
    bsa_set(testBsa, 20, 40);
    int mRow = get_MasterRow(20);
    int pos20 = get_CellPos(20);
    assert(mRow == 4);
    assert(pos20 == 5);
    assert(testBsa->masterRow[mRow]->inUse[pos20] == true);
    free_inUse(testBsa->masterRow[mRow]);
    assert(!testBsa->masterRow[mRow]->inUse);

    // Testing Function 8: bsa_maxindex + helper:
    bsa_set(testcompareBSA, 17, 30);
    assert(findX(testcompareBSA, mRow) == 17);
    bsa_set(testcompareBSA, 18, 50);
    assert(bsa_maxindex(testcompareBSA) == 18);

    // Testing Function 9: bsa_tostring, bsa_tostring_row, bsa_tostring_cell:
    char str[1000] = "";
    bsa_tostring(testcompareBSA, str);
    assert(strcmp(str, "{}{}{}{[8]=101}{[17]=30 [18]=50}") == 0);

    // Testing Function: bsa_tostring_row
    char rowStr[1000] = "";
    bsa_tostring_row(testcompareBSA, 4, rowStr);
    assert(strstr(rowStr, "[17]=30 [18]=50") != NULL);

    // Testing Function: bsa_tostring_cell
    char cellStr[1000] = "";
    int pos8MR = get_MasterRow(8);
    int pos8end = get_CellRowEnd(8);
    assert(testcompareBSA->masterRow[pos8MR]->cellRow[1] == 101);
    assert(testcompareBSA->masterRow[pos8MR]->inUse[1] == true);
    bsa_tostring_cell(testcompareBSA, pos8MR, 8, pos8end, cellStr);
    assert(strcmp(cellStr, "[8]=101") == 0);

    bsa_free(testBsa); 
    bsa_free(testcompareBSA);
}

