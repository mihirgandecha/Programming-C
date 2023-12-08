#include "specific.h"

//start init func
bsa* bsa_init(void){
    bsa* emptyBSA;
    //Allocate memory for 1 whole bsa structure
    emptyBSA = (bsa*) calloc(1, sizeof(bsa)); 
    if (emptyBSA == NULL){
        return NULL;
    }
    for (int bsaRow = 0; bsaRow < BSA_ROWS; bsaRow++){
        emptyBSA->masterRow[bsaRow] = NULL;
    }
    test_firstInit(emptyBSA);
    return emptyBSA;
}

bool test_firstInit(bsa *b){ //Test bsa has dAllocSize of 1, and 0->29 is set to 0
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
//end init func

//check indx in bound
bool is_indxinBound(int indx){
    if ((indx >= OUTBOUND_END) || (indx <= OUTBOUND)){
        return false;
    }
    return true;
}
//TODO just move to end
void asserttest_indxbound(void){
    int indx = 1073741824;
    assert(is_indxinBound(indx));
}
//end indx in bound

//start here bsa_set
bool bsa_set(bsa* b, int indx, int d) {
    if (!check_initial_conditions(b, indx)) {
        return false;
    }
    int k = 0;
    k = kth_row(indx, &k);
    if (!handle_row_allocation(b, k) || !handle_child_allocation(b, k)) {
        return false;
    }
    return set_value(b, indx, d);
}


bool check_initial_conditions(bsa* b, int indx){ 
    return b != NULL && b->masterRow != NULL && is_indxinBound(indx);
}

bool handle_row_allocation(bsa* b, int k) {
    if (b->masterRow[k] == NULL) {
        return allocate2_BSAROW(b, k);
    }
    return true;
}

bool allocate2_BSAROW(bsa* b, int k){
    // Allocate only if b->masterRow[k] is NULL
    if (b->masterRow[k] == NULL){ 
        b->masterRow[k] = (Cell_Row*)calloc(1, sizeof(Cell_Row));
        if (b->masterRow[k] == NULL){
            return false; // Allocation failed
        }
    }
    return true; // Allocation succeeded or was not needed
}

bool handle_child_allocation(bsa* b, int k) {
    if (b->masterRow[k] != NULL && b->masterRow[k]->cellRow == NULL) {
        return allocate3_rowlen(b, k);
    }
    return b->masterRow[k] != NULL;
}

bool allocate3_rowlen(bsa* b, int k){
    int rowLen = row_len(k);
    if (b->masterRow[k]->cellRow == NULL){
        b->masterRow[k]->cellRow = (int*)calloc(rowLen, sizeof(int)); // Allocating memory for the cellRow array
        if (b->masterRow[k]->cellRow == NULL){ // Corrected check
            return false; // Allocation failed
        }
        b->masterRow[k]->isD_Allocated = (bool*)calloc(rowLen, sizeof(bool));
        if (b->masterRow[k]->isD_Allocated == NULL){ // Corrected check
            // free(b->masterRow[k]->cellRow); // Free previously allocated memory
            return false; // Allocation failed
        }
        for (int i = 0; i < rowLen; i++){
            b->masterRow[k]->isD_Allocated[i] = false;
        }
    } 
    return true; // Allocation succeeded or was not needed
}

bool set_value(bsa* b, int indx, int d) {
    int k = 0;
    k = kth_row(indx, &k);
    b->masterRow[k]->cellRow_Start = index_start(k);
    b->masterRow[k]->cellRow_End = index_end(k);
    b->masterRow[k]->cellrow_Len = row_len(k);
    int position = indx - b->masterRow[k]->cellRow_Start;
    if (position < 0 || position > b->masterRow[k]->cellRow_End) {
        return false;
    }
    b->masterRow[k]->cellRow[position] = d;
    b->masterRow[k]->isD_Allocated[position] = true;
    b->masterRow[k]->dAllocSize += 1;
    return true;
}

//maybe redo or remove:
void asserttest_secondAlloc(void){ //works
    bsa* testBsa = bsa_init();
    int indx = 7;
    int k = 0;
    k = kth_row(indx, &k); //should be 3
    allocate2_BSAROW(testBsa, k);
    assert(testBsa->masterRow[k] != NULL);
    bsa_free(testBsa);
}


void asserttest_ThirdAlloc(void){
    bsa* testBsa = bsa_init();
    int indx = 7;
    int k = 0;
    k = kth_row(indx, &k); //should be 3
    allocate2_BSAROW(testBsa, k);
    allocate3_rowlen(testBsa, k);
    int rowLen = row_len(k);
    for (int i = 0; i < rowLen; i++){
        assert(testBsa->masterRow[k]->cellRow[i] == 0);
    }
    bsa_free(testBsa);
}


//do I need?
bool is_ChildRowAloc(bsa* b, int k){
    if ((test_firstInit(b) == false) && (b->masterRow[k] == NULL) && (b->masterRow[k]->cellRow ==NULL)){
        return false;
    }
    return true;
}


int kth_row(int index, int *k) { 
    if (*k >= BSA_ROWS) {
        return OUTBOUND; 
    }
    int iS = index_start(*k);
    int iE = index_end(*k);
    if ((index >= iS) && (index <= iE)){
        testK(*k);
        return *k;
    } 
    else {
        (*k)++;
        return kth_row(index, k);
    }
}

void test_kRow(void){ //works
    int k = 0;
    assert(kth_row(0, &k) == 0);
    k = 0;
    assert(kth_row(1, &k) == 1);
    k = 0;
    assert(kth_row(2, &k) == 1);
    k = 0;
    assert(kth_row(3, &k) == 2);//works now
    k = 0;
    assert(kth_row(6, &k) == 2); 
    k = 0;
    assert(kth_row(7, &k) == 3); 
    k = 0;
    assert(kth_row(14, &k) == 3);
    k = 0;
    assert(kth_row(30, &k) == 4); 
    k = 0;
    assert(kth_row(128, &k) == 7);
}

int row_len(int k){
    if (k == 0){
        return 1;
    }
    return (1L << k);
}

void test_int_rowLen(void){
    assert(row_len(0) == 1);
    assert(row_len(1) == 2);
    assert(row_len(2) == 4);
    assert(row_len(3) == 8);
    //sep func: void test rowLen == below
    // bsa* testBSA = bsa_init();
    // int index = 5;
    // int k = kth_row;
    // int rowStart = index_start(k);
    // int rowEnd = index_end(k);
    // int rowLen = int rowLen(k);
    // assert(rowLen == ((rowEnd - rowStart) + 1));
}

int index_start(int k){
    if (k == 0){
        return 0;
    }
    return (1L << k) - 1;
}

void testIstart(void){
    assert(index_start(0) == 0);
    assert(index_start(1) == 1);
    assert(index_start(2) == 3);
    assert(index_start(3) == 7);
    assert(index_start(4) == 15);
    assert(index_start(5) == 31);
    assert(index_start(6) == 63);
    assert(index_start(BSA_ROWS - 1) == 536870911); //last row 29
}

int index_end(int k){
    if (k == 0){
        return 0;
    }
    return (1L << (k + 1)) - 2;
}

void testIend(void){
    assert(index_end(0) == 0);
    assert(index_end(1) == 2);
    assert(index_end(2) == 6);
    assert(index_end(7) == 254);
    assert(index_end(8) == 510);
    assert(index_end(9) == 1022);
    assert(index_end(10) == 2046);
    assert(index_end(11) == 4094);
    assert(index_end(BSA_ROWS - 1) == 1073741822);
}

bool testK(int k){ 
    if ((k < 0) || (k >= BSA_ROWS)){
        return false;
    }
    return true;
}

void test_testK(void){ 
    int k;
    k = -3;
    assert(testK(k) == false);

    k = BSA_ROWS;
    assert(testK(k) == false);
}

// Return pointer to data at element b[i]
// or NULL if element is unset, or part of a row that hasn't been allocated.
int* bsa_get(bsa* b, int indx){
    if (!check_initial_conditions(b, indx)) {
        return NULL;
    } //ok bsa is allocated and indx is in range
    int k = 0;
    kth_row(indx, &k);
    if (b->masterRow[k] == NULL || b->masterRow[k]->cellRow == NULL) { //there is func for this
        return NULL; //perhaps is is_ChildRowAloc
    }
    int position = indx - b->masterRow[k]->cellRow_Start;
    if (position < 0 || position >= b->masterRow[k]->cellrow_Len) {
        return NULL;
    }
    return &(b->masterRow[k]->cellRow[position]);
}


int find_child_position(bsa* b, int k, int indx) {
    if (b == NULL || b->masterRow[k] == NULL || indx < b->masterRow[k]->cellRow_Start || indx >= b->masterRow[k]->cellRow_Start + b->masterRow[k]->cellrow_Len) {
        return OUTBOUND;
    }
    return indx - b->masterRow[k]->cellRow_Start;
}

bool bsa_delete(bsa* b, int indx) {
    if (check_initial_conditions(b, indx) == false){ //return b != NULL && b->masterRow != NULL && is_indxinBound(indx);
        return false;
    }
    int k = 0;
    k = kth_row(indx, &k);
    if(b->masterRow[k]->cellRow == NULL){
        return false;
    }
    int currentPosition = find_child_position(b, k, indx);
    if (b->masterRow[k]->isD_Allocated[currentPosition] == false){
        return false;
    }
    int cellsAllocated = b->masterRow[k]->dAllocSize;
//another function
    if (cellsAllocated == 1){
        if(b->masterRow[k]->cellRow != NULL){
            free(b->masterRow[k]->cellRow);
            // b->masterRow[k]->cellRow = NULL;
        }
        if(b->masterRow[k]->isD_Allocated != NULL){
            free(b->masterRow[k]->isD_Allocated);
            b->masterRow[k]->isD_Allocated = NULL;
        }
        free(b->masterRow[k]);
        b->masterRow[k] = NULL;
        return true;
    }

//one function
    if (cellsAllocated > 1){
        b->masterRow[k]->cellRow[currentPosition] = EMPTY;
        b->masterRow[k]->isD_Allocated[currentPosition] = false;
        b->masterRow[k]->dAllocSize -= 1;
        return true;
    }
    return false;
}

bool bsa_free(bsa* b) {
    if (b == NULL) {
        return false;
    }
    for (int i = 0; i < BSA_ROWS; i++) {
        if (b->masterRow[i] != NULL) {
            if(b->masterRow[i]->cellRow != NULL){
                free(b->masterRow[i]->cellRow);
                b->masterRow[i]->cellRow = NULL;
            }
            if(b->masterRow[i]->isD_Allocated != NULL){
                free(b->masterRow[i]->isD_Allocated);
                b->masterRow[i]->isD_Allocated = NULL;
            }
            free(b->masterRow[i]);
            b->masterRow[i] = NULL;
        }
    }
    free(b);
    return true;
}
// bool bsa_free(bsa* b) {
//     if (b == NULL) {
//         return false;
//     }
//     for (int i = 0; i < BSA_ROWS; i++){
//         if((b->masterRow != NULL) && (b->masterRow[i] != NULL)){
//             bsa_freeData(b, i);
//         }
//         else if (b->masterRow[i] != NULL){
//             free(b->masterRow[i]);
//                 if (b->masterRow[i] != NULL){
//                     return false; // Allocation failed
//                 }
//         }
//     }
//     free(b);
//     return true;
// }

// bool bsa_freeData(bsa* b, int bsaRow){
//     // if(b->masterRow == NULL){
//     //     return false;
//     // }
//     // if(b->masterRow[bsaRow] == NULL){
//     //     return false;
//     // }
//     // int rowLen = b->masterRow[bsaRow]->rowLen;
//     // for (int currentPosition = b->masterRow[bsaRow]->cellRow_Start; currentPosition < rowLen; currentPosition++){
//     //     free(&b->masterRow[bsaRow]->cellRow[currentPosition]);
//     //     free(&b->masterRow[bsaRow]->isD_Allocated[currentPosition]);
//     // }
//     free(b->masterRow[bsaRow]->isD_Allocated);
//     free(b->masterRow[bsaRow]->cellRow);
//     // if (b->masterRow[bsaRow]->cellRow != NULL){
//     //     return false; // Allocation failed
//     // }
//     free(b->masterRow);
//     return true;
// }


// bool bsa_free(bsa* b) {
//     if (b == NULL){
//         return false;
//     }
//     for (int bsaPointer = 0; bsaPointer < BSA_ROWS; bsaPointer++){
//         if (b->masterRow[bsaPointer] == NULL){
//             free(b->masterRow[bsaPointer]);
//             return true;
//         }
//         if ((b->masterRow[bsaPointer] != NULL) && (b->masterRow[bsaPointer]->cellRow != NULL)){
//             free(b->masterRow[bsaPointer]->cellRow);
//         }
//         else if(b->masterRow[bsaPointer]->isD_Allocated != NULL){
//             free(b->masterRow[bsaPointer]->isD_Allocated);
//         }
//     }
//     free(b);
//     return true;
// }

// Returns maximum index written to so far or
// -1 if no cells have been written to yet
int bsa_maxindex(bsa* b){
    if ((b == NULL) || (b->masterRow == NULL)){
        return OUTBOUND;
    }
    for (int bsaRow = MAX_MASTERROW; bsaRow >= 0; bsaRow--){
        if (b->masterRow[bsaRow] != NULL){
            //make int variables
            // printf("bsaRow: %i, Kstart: %i, Kend: %i\n", bsaRow, b->masterRow[bsaRow]->cellRow_Start, b->masterRow[bsaRow]->cellRow_End);
            for(int maxIndex = b->masterRow[bsaRow]->cellRow_End; maxIndex >= b->masterRow[bsaRow]->cellRow_Start; maxIndex--){
                if(b->masterRow[bsaRow]->isD_Allocated[maxIndex - b->masterRow[bsaRow]->cellRow_Start] == true){
                    return maxIndex;
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
    int k = 0;
    k = kth_row(maxIndex, &k);
    for (int bsaRow = 0; bsaRow <= k; bsaRow++){
        bsa_tostring_row(b, bsaRow, str);
    }
    return true;
}

void bsa_tostring_row(bsa* b, int bsaRow, char* str){
    if (b->masterRow[bsaRow] == NULL){
        strcat(str, "{}");
    }
    else{
        int cellStart = b->masterRow[bsaRow]->cellRow_Start;
        int cellEnd = b->masterRow[bsaRow]->cellRow_End; 
        strcat(str, "{");
        for(int currentPosition = cellStart; currentPosition <= cellEnd; currentPosition++){
            bsa_tostring_cell(b, bsaRow, currentPosition, str);
        }
        strcat(str, "}");
    }
}

void bsa_tostring_cell(bsa* b, int bsaRow, int currentPosition, char* str){
    int cellDifference = currentPosition - b->masterRow[bsaRow]->cellRow_Start;
    if(b->masterRow[bsaRow]->isD_Allocated[cellDifference] == 1){
        char temp[1000]; 
        sprintf(temp, "[%d]=%d", currentPosition, b->masterRow[bsaRow]->cellRow[cellDifference]);
        strcat(str, temp); //make variable below
        if (currentPosition != b->masterRow[bsaRow]->cellRow_End && b->masterRow[bsaRow]->isD_Allocated[cellDifference + 1] == true){
            strcat(str, " ");
        }
    }
}

// Allow a user-defined function to be applied to each (valid) value 
// in the array. The user defined 'func' is passed a pointer to an int,
// and maintains an accumulator of the result where required.
void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc){
    //from the max k and find max cellRow_End --ie go through k from 29->0, if been allocated, access and find max index
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
    test_kRow();
    testIstart();
    testIend();
    test_testK();
    test_int_rowLen();
    test_testK();
  
}
