#include "specific.h"

//start init func
bsa* bsa_init(void){
    bsa* emptyBSA;
    //Allocate memory for 1 whole bsa structure
    emptyBSA = (bsa*) calloc(1, sizeof(bsa)); 
    if (emptyBSA == NULL){
        return NULL;
    }
    //Set pointers 0-29 to NULL (delete and free func reasons) TODO: does malloc decrease functin lines?
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
    for (int bsaRow = 0; bsaRow < BSA_ROWS; bsaRow++) {
        if (b->masterRow[bsaRow] != NULL){
            return false;
        }
    }
    return true;
}

//check indx in bound
bool is_indxinBound(int indx){
    if ((indx >= OUTBOUND_END) || (indx <= OUTBOUND)){
        return false;
    }
    return true;
}

//start here bsa_set
bool bsa_set(bsa* b, int indx, int d) {
    if (!check_initial_conditions(b, indx)) {
        return false;
    }
    int mRowVal = get_MasterRow(indx);
    if (!check_AllocCellRow(b, mRowVal) || !check_alocCellStruct(b, mRowVal)) {
        return false;
    }
    return set_value(b, indx, d);
}


bool check_initial_conditions(bsa* b, int indx){ 
    return b != NULL && b->masterRow != NULL && is_indxinBound(indx);
}

bool check_AllocCellRow(bsa* b, int mRowVal) {
    if (b->masterRow[mRowVal] == NULL) {
        return alloc_CellStruct(b, mRowVal);
    }
    return true;
}

bool alloc_CellStruct(bsa* b, int mRowVal){
    // Allocate only if b->mRowVal[mRowVal] is NULL
    if (b->masterRow[mRowVal] == NULL){ 
        b->masterRow[mRowVal] = (Cell_Row*)calloc(1, sizeof(Cell_Row));
        if (b->masterRow[mRowVal] == NULL){
            return false; // Allocation failed
        }
    }
    return true; // Allocation succeeded or was not needed
}

bool check_alocCellStruct(bsa* b, int mRowVal) {
    if (b->masterRow[mRowVal] != NULL && b->masterRow[mRowVal]->cellRow == NULL) {
        return alloc_CellRow(b, mRowVal);
    }
    return b->masterRow[mRowVal] != NULL;
}

bool alloc_CellRow(bsa* b, int mRowVal){
    int rowLen = get_cellLen(mRowVal);
    if (b->masterRow[mRowVal]->cellRow == NULL){
        b->masterRow[mRowVal]->cellRow = (int*)calloc(rowLen, sizeof(int)); // Allocating memory for the cellRow array
        if (b->masterRow[mRowVal]->cellRow == NULL){ // Corrected check
            return false; // Allocation failed
        }
        b->masterRow[mRowVal]->inUse = (bool*)calloc(rowLen, sizeof(bool));
        if (b->masterRow[mRowVal]->inUse == NULL){ // Corrected check
            // free(b->masterRow[mRowVal]->cellRow); // Free previously allocated memory TODO
            return false;
        }
        for (int i = 0; i < rowLen; i++){
            b->masterRow[mRowVal]->inUse[i] = false;
        }
    } 
    return true; // Allocation succeeded or was not needed
}

bool set_value(bsa* b, int indx, int d) {
    int mRowVal = get_MasterRow(indx);
    b->masterRow[mRowVal]->start = get_CellRowStart(mRowVal);
    b->masterRow[mRowVal]->end = get_CellRowEnd(mRowVal);
    b->masterRow[mRowVal]->length = get_cellLen(mRowVal);
    int position = indx - b->masterRow[mRowVal]->start;
    if (position < 0 || position > b->masterRow[mRowVal]->end) {
        return false;
    }
    b->masterRow[mRowVal]->cellRow[position] = d;
    b->masterRow[mRowVal]->inUse[position] = true;
    b->masterRow[mRowVal]->size += 1;
    return true;
}

// //maybe redo or remove:
// void asserttest_secondAlloc(void){ //works
//     bsa* testBsa = bsa_init();
//     int indx = 7;
//     int mRowVal = 0;
//     mRowVal = get_MasterRow(indx, &mRowVal); //should be 3
//     alloc_CellStruct(testBsa, mRowVal);
//     assert(testBsa->masterRow[mRowVal] != NULL);
//     bsa_free(testBsa);
// }


void asserttest_ThirdAlloc(void){
    bsa* testBsa = bsa_init();
    int indx = 7;
    int mRowVal = get_MasterRow(indx); //should be 3
    alloc_CellStruct(testBsa, mRowVal);
    alloc_CellRow(testBsa, mRowVal);
    int rowLen = get_cellLen(mRowVal);
    for (int i = 0; i < rowLen; i++){
        assert(testBsa->masterRow[mRowVal]->cellRow[i] == 0);
    }
    bsa_free(testBsa);
}


//do I need?
bool is_ChildRowAloc(bsa* b, int mRowVal){
    if ((test_firstInit(b) == false) && (b->masterRow[mRowVal] == NULL) && (b->masterRow[mRowVal]->cellRow ==NULL)){
        return false;
    }
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
    return 0;
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

void testget_CellRowStart(void){
    assert(get_CellRowStart(0) == 0);
    assert(get_CellRowStart(1) == 1);
    assert(get_CellRowStart(2) == 3);
    assert(get_CellRowStart(3) == 7);
    assert(get_CellRowStart(4) == 15);
    assert(get_CellRowStart(5) == 31);
    assert(get_CellRowStart(6) == 63);
    assert(get_CellRowStart(BSA_ROWS - 1) == 536870911); //last row 29
}

int get_CellRowEnd(int mRowVal){
    if (mRowVal == 0){
        return 0;
    }
    return (1L << (mRowVal + 1)) - 2;
}


bool is_MasterinBound(int mRowVal){ 
    if ((mRowVal < 0) || (mRowVal >= BSA_ROWS)){
        return false;
    }
    return true;
}

void testis_MasterinBound(void){ 
    int mRowVal;
    mRowVal = -3;
    assert(is_MasterinBound(mRowVal) == false);

    mRowVal = BSA_ROWS;
    assert(is_MasterinBound(mRowVal) == false);
}

// Return pointer to data at element b[i]
// or NULL if element is unset, or part of a row that hasn't been allocated.
int* bsa_get(bsa* b, int indx){
    if (!check_initial_conditions(b, indx)) {
        return NULL;
    } //ok bsa is allocated and indx is in range
    int mRowVal = get_MasterRow(indx);
    if (b->masterRow[mRowVal] == NULL || b->masterRow[mRowVal]->cellRow == NULL) { //there is func for this
        return NULL; //perhaps is is_ChildRowAloc
    }
    int position = indx - b->masterRow[mRowVal]->start;
    if (position < 0 || position >= b->masterRow[mRowVal]->length) {
        return NULL;
    }
    return &(b->masterRow[mRowVal]->cellRow[position]);
}


int find_child_position(bsa* b, int mRowVal, int indx) {
    int cellStart = b->masterRow[mRowVal]->start;
    int cellLen = b->masterRow[mRowVal]->length;
    if (b == NULL || b->masterRow[mRowVal] == NULL || indx < cellStart || indx >= cellStart + cellLen) {
        return OUTBOUND;
    }
    return indx - b->masterRow[mRowVal]->start;
}

bool bsa_delete(bsa* b, int indx){
    if (check_initial_conditions(b, indx) == false){
        return false;
    }
    int mRowVal = get_MasterRow(indx);
    int currentPosition = find_child_position(b, mRowVal, indx);
    if (!b->masterRow[mRowVal]->inUse[currentPosition]){
        return false;
    }
    if (b->masterRow[mRowVal]->size == 1){
        if(!bsa_freerow(b, mRowVal)){
            return false;
        }
        return true;
    }
    if (b->masterRow[mRowVal]->size > 1){
        delete_helper(b, currentPosition, mRowVal);
        return true;
    }
    return false;
}

bool bsa_freerow(bsa* b, int mRowVal){
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

void delete_helper(bsa* b, int currentPosition, int mRowVal){
    b->masterRow[mRowVal]->cellRow[currentPosition] = 0;
    b->masterRow[mRowVal]->inUse[currentPosition] = false;
    b->masterRow[mRowVal]->size -= 1;
}

bool bsa_free(bsa* b) {
    if (b == NULL) {
        return false;
    }
    for (int mRowVal = 0; mRowVal < BSA_ROWS; mRowVal++) {
        if (b->masterRow[mRowVal] != NULL) {
            if(b->masterRow[mRowVal]->cellRow != NULL){
                free(b->masterRow[mRowVal]->cellRow);
                b->masterRow[mRowVal]->cellRow = NULL;
            }
            if(b->masterRow[mRowVal]->inUse != NULL){
                free(b->masterRow[mRowVal]->inUse);
                b->masterRow[mRowVal]->inUse = NULL;
            }
            free(b->masterRow[mRowVal]);
            b->masterRow[mRowVal] = NULL;
        }
    }
    free(b);
    return true;
}

int bsa_maxindex(bsa* b){
    if (!b || !b->masterRow){
        return OUTBOUND;
    }
    for (int rowY = MAX_MASTERROW; rowY >= 0; rowY--){
        if (b->masterRow[rowY] != NULL){ 
            int cellStart = b->masterRow[rowY]->start;
            for(int rowXMax = b->masterRow[rowY]->end; rowXMax >= cellStart; rowXMax--){
                if(b->masterRow[rowY]->inUse[rowXMax - cellStart]){
                    return rowXMax;
                }
            }
        }
    }
    return OUTBOUND;
}

//To String Function:
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
        for(int i = cellStart; i <= cellEnd; i++){
            bsa_tostring_cell(b, bsaRow, i, cellEnd, str);
        }
        strcat(str, "}");
    }
}

void bsa_tostring_cell(bsa* b, int bsaRow, int currentPosition, int cellEnd, char* str){
    int cellDifference = currentPosition - b->masterRow[bsaRow]->start;
    if(b->masterRow[bsaRow]->inUse[cellDifference] == 1){
        char temp[1000]; 
        sprintf(temp, "[%d]=%d", currentPosition, b->masterRow[bsaRow]->cellRow[cellDifference]);
        strcat(str, temp); //make variable below
        if (currentPosition != cellEnd && b->masterRow[bsaRow]->inUse[cellDifference + 1] == true){
            strcat(str, " ");
        }
    }
}

// Allow a user-defined function to be applied to each (valid) value 
// in the array. The user defined 'func' is passed a pointer to an int,
// and maintains an accumulator of the result where required.
void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc){
    //from the max mRowVal and find max end --ie go through mRowVal from 29->0, if been allocated, access and find max index
    int max_index = bsa_maxindex(b);
    for (int i = 0; i <= max_index; i++){
        //performing for each bsa_get works for
        int* q = bsa_get(b, i);
        if (q != NULL){
            func(q, acc);
        }
    }
}


void test(void){
    assert(!is_indxinBound(OUTBOUND));

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

    //Test Cell Row Length:
    assert(get_CellRowStart(4) == 15);
    assert(get_CellRowStart(5) == 31);
    assert(get_CellRowStart(6) == 63);
    assert(get_CellRowStart(BSA_ROWS - 1) == 536870911); //last row 29

    //Check index in bound:
    //Check second allocation:
    bsa* testBsa = bsa_init();
    int indx = 7;
    int mRowVal = get_MasterRow(indx); //should be 3
    alloc_CellStruct(testBsa, mRowVal);
    assert(testBsa->masterRow[mRowVal] != NULL);
    bsa_free(testBsa);  
}
