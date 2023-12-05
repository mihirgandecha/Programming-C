#include "specific.h"

bsa* bsa_init(void){
    bsa* emptyBSA;
    emptyBSA = (bsa*) calloc(1, sizeof(bsa)); //allocate one size for whole bsa structure
    if (emptyBSA == NULL){
        return NULL;
    }    
    for (int i = 0; i < BSA_ROWS; i++){
        emptyBSA->master[i] = NULL;
    }
    return emptyBSA;
}

bool test_firstInit(bsa *b){ //different function for testInit for Child?
    if (b == NULL){
        return false;
    }
    for (int bsaRow = 0; bsaRow < BSA_ROWS; bsaRow++) {
        if (b->master[bsaRow] != NULL){
            return false;
        }
    }
    return true;
}

// Set element at index indx (2^k) with value d i.e. b[i] = d;
// May require an allocation if it's the first element in that row
bool bsa_set(bsa* b, int indx, int d){
    //Check that b has been initialised first as NULL return false indicates bsa allocation did not work
    if (test_firstInit(b) == false){
        b = bsa_init();
    } 
    if ((indx >= OUTBOUND_END) || (indx <= OUTBOUND)){
        return false;
    } 
    //first calculating kth row given the index
    int k = 0;
    k = kth_row(indx, &k); //remove
    int rowLen = row_len(k);
    if (allocateChild(b, k, rowLen) == false){
        return false;
    }
    storeData(b, k, rowLen);
    //set value d into the created row - keep here
    int position = indx - b->master[k]->kStart; //could this be an array of pointers?
    b->master[k]->child[position] = d;
    return true;
}

bool allocateChild(bsa* b, int k, int rowLen){
    if (!test_firstInit(b)){
        return false;
    }
    if (!testK(k)){
        return false;
    }
    if (b->master[k] == NULL){ 
        b->master[k] = (BSA_Row*)calloc(1, sizeof(BSA_Row)); //allocating memory for BSA structure for the pointer 
        if (b->master[k] == NULL){
            return false;
        }
    }
    if (b->master[k]->child == NULL){
        b->master[k]->child = (int*)calloc(rowLen, sizeof(int)); //allocating memory for BSA structure for the pointer
    }
    if (is_ChildAloocated(b, k) == false){
        return false;
    }
    if (isRowEmpty(b, k, rowLen) == false){
        return false;
    }
    return true;
}

bool is_ChildAloocated(bsa* b, int k){
    if ((test_firstInit(b) == false) && (b->master[k] == NULL) && (b->master[k]->child ==NULL)){
        return false;
    }
    return true;
}

bool isRowEmpty(bsa* b, int k, int rowLen){
    for (int i = 0; i < rowLen; i++){
        if(b->master[k]->child[i] != 0){
            return false;
        }
    }
    return true;
}

bool testall(bsa* b, int k, int rowLen){
    if (!test_firstInit(b)){
        return false;
    }
    if (!is_ChildAloocated(b, k)){
        return false;
    }
    if (!isRowEmpty(b, k, rowLen)){
        return false;
    }
    return true;
}

void storeData(bsa* b, int k, int rowLen){
    b->master[k]->kthRow = k;
    b->master[k]->kStart = index_start(k);
    b->master[k]->kEnd = index_end(k); 
    b->master[k]->rowLen = rowLen;
    return;
}

int kth_row(int index, int *k) { 
    if (*k >= BSA_ROWS) {
        return OUTBOUND; 
    }
    int iS = index_start(*k);
    int iE = index_end(*k);
    if ((index >= iS) && (index <= iE)) {
        return *k;
    } else {
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
    if (test_firstInit(b) == false){
        return NULL;
    }
    for (int bsaRow = 0; bsaRow < BSA_ROWS; bsaRow++){ //rename 
        for (int row = 0; row < b->master[bsaRow]->rowLen; row++){
            if ((b->master[bsaRow]->child != NULL) && (b->master[bsaRow]->child[row] == indx)){
                return &(b->master[bsaRow]->child[row]);
            }
        }
    }
    return NULL;
}

// Delete element at index indx - forces a shrink
// if that was the only cell in the row occupied.
bool bsa_delete(bsa* b, int indx){ //del after: use free function for delete. Delete row if nothing is set
    //has bsa been allocated
    if(!test_firstInit(b)){
        return false;
    }
    int k = 0;
    k = kth_row(indx, &k);
    if(!is_ChildAloocated(b, k)){
        return false;
    }
    if(isRowEmpty(b, k, b->master[k]->rowLen) == true){
        printf("Everything is already empty");
        return false;
    }
    int counter = 0;
    if(!isRowEmpty(b, k, b->master[k]->rowLen)){
        for(int rowIndex = 0; rowIndex < b->master[k]->rowLen; rowIndex++){
            if(b->master[k]->child[rowIndex] != EMPTY){
                counter++;
            }
        }
    }
    if (counter == 1){
        int position = indx - b->master[k]->kStart;
        b->master[k]->child[position] = EMPTY;
        printf("One has been deleted!\n");
    }
    if (counter > 1){
        (allocateChild(b, k, b->master[k]->rowLen));
        printf("many has been delted!\n");
    }
    return true;
}

// Returns maximum index written to so far or
// -1 if no cells have been written to yet
int bsa_maxindex(bsa* b){
    if ((b == NULL) || (b->master == NULL)){
        return OUTBOUND;
    }
    int maxIndex = OUTBOUND;
    
    for (int bsaRow = 0; bsaRow < BSA_ROWS; bsaRow++){
        if (b->master[bsaRow] != NULL && b->master[bsaRow]->child != NULL){
            for (int childRow = 0; childRow < b->master[bsaRow]->rowLen; childRow++){
                if (b->master[bsaRow]->child[childRow] != 0 && childRow > maxIndex){
                    maxIndex = childRow;
                }
            }
        }
    }
    return maxIndex;
}


// Clears up all space used
bool bsa_free(bsa* b){
    if (b == NULL){
        printf("bsa not init\n");
        return false;
    }
    for (int bsaRow = 0; bsaRow < BSA_ROWS; bsaRow++){
        if (b->master[bsaRow] != NULL){
            if (b->master[bsaRow]->child != NULL){
                free(b->master[bsaRow]->child);
                printf("contents of row freed\n");
            }
            free(b->master[bsaRow]);
            printf("the bsa_row struct has been freed within row\n");
        }
    }
    free(b); // Free the bsa structure itself
    printf("bsa structure freed\n");
    return true;
}

// Allow a user-defined function to be applied to each (valid) value 
// in the array. The user defined 'func' is passed a pointer to an int,
// and maintains an accumulator of the result where required.
// void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc){
//     return;
//     if (func != NULL) {
//         func(&b->array, acc); 
//     }
// }

// // You'll this to test the other functions you write
// TODO: Does software turn off house style when function test are declared? 

void test(void){
    // bsa* testArray = bsa_init();
    // for (int testcolP = 0; testcolP < BSA_ROWS; testcolP++){
    //     assert(&testArray->array[testcolP] == NULL);
    // }
    // free(testArray);

    test_kRow();
    testIstart();
    testIend();
    
    test_testK();

    // bsa_set2(testArray, (MAXEND_INDEX + 1), 10);    
}
