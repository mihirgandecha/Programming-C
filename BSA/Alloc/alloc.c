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
    // if (test_firstInit(emptyBSA) == false){
    //     return NULL;
    // }
    return emptyBSA;
}

bool test_firstInit(bsa *b){ //different function for testInit for Child?
    if (b == NULL || b->master == NULL){
        return false;
    }
    return true;
}

// void assert_firstInit(void){
//     bsa *noAlloc = OUTBOUND;
//     assert(test_firstInit(noAlloc) == false);

//     bsa *allocated = bsa_init();
//     assert(test_firstInit(allocated) == true);
//     bsa_free(allocated);
// }

// Set element at index indx (2^k) with value d i.e. b[i] = d;
// May require an allocation if it's the first element in that row
bool bsa_set(bsa* b, int indx, int d){
    //Check that b has been initialised first as NULL return false indicates bsa allocation did not work
    if (test_firstInit(b) == false){
        return false;
    } //works
    if ((indx >= OUTBOUND_END) || (indx <= OUTBOUND)){
        return false;
    } 
    //first calculating kth row given the index
    int k = kth_row(indx); //remove
    if (storeData(b, k) == false){
        return false;
    }
    //set value d into the created row - keep here
    int position = indx - b->master[k]->kStart;
    b->master[k]->child[position] = d;
    return true;
}

bool storeData(bsa* b, int k){
    if (test_firstInit(b) == false){
        return false;
    }
    b->master[k]->kStart = index_start(k);
    b->master[k]->kEnd = index_end(k); 
    b->master[k]->rowLen = (b->master[k]->kEnd - b->master[k]->kStart) + 1; //function? - want to make 4 - works!

    if (b->master[k]->child == NULL){ //yessss
        b->master[k]->child = (int*)calloc(b->master[k]->rowLen, sizeof(int));
        if (b->master[k]->child == NULL){
            return false;
        }  
    }
    return true;
}

int kth_row(int index){ //pass b too?
    int iS = index_start(index); //works
    int iE = index_end(index);

    if((index >= iS) && (index <= iE)){
        return index;
    }
    else{
        index += 1;
        return kth_row(index);
    }
}
// void test_storeData(void){
//     bsa* testBSA = bsa_init();
//     int k = 0;

// }

// void test_krowNew(void){ //works
//     int k;
//     k = 0;
//     assert(kth_row(0, &k) == 0);
//     k = 0;
//     assert(kth_row(1, &k) == 1);
//     k = 0;
//     assert(kth_row(2, &k) == 1);
//     k = 0;
//     assert(kth_row(3, &k) == 2);//works now
//     k = 0;
//     assert(kth_row(6, &k) == 2); 
//     k = 0;
//     assert(kth_row(7, &k) == 3); 
//     k = 0;
//     assert(kth_row(14, &k) == 3);
//     k = 0;
//     assert(kth_row(30, &k) == 4); 
//     k = 0;
//     assert(kth_row(128, &k) == 7);
// }

void test_kRow(void){ //works
    assert(kth_row(0) == 0);
    assert(kth_row(1) == 1);
    assert(kth_row(2) == 1);
    assert(kth_row(3) == 2);//works now
    assert(kth_row(6) == 2); 
    assert(kth_row(7) == 3); 
    assert(kth_row(14) == 3);
    assert(kth_row(30) == 4); 
    assert(kth_row(128) == 7);
}

// int kth_row(int index, int *k){ //pass b too?
//     int iS = index_start(*k); //works
//     int iE = index_end(*k);

//     if((index >= iS) && (index <= iE)){
//         return *k;
//     }
//     else{
//         *k += 1;
//         return kth_row(index, k);
//     }
// }


// int find_masterrow(int k, int indx){
//     int tempK = kth_row(indx, &tempK); //k to be 2
//     //Check that kth row is in bound, false if 30 or higher
//     if (testK(k) == false){
//         return OUTBOUND;
//     }
//     return tempK;
// }

// bool is_indxInbound(int index, int rowStart, int rowEnd){
//     if ((index <= OUTBOUND) || (index >= OUTBOUND_END)){
//         return false;
//     }
//     if ((index <= rowStart) || (index >= rowEnd)){
//         return false;
//     }
//     return true;  
// }

// void test_is_indxInbound(void){
//     int index = 0;
//     int masterRow = kth_row(index);
//     int rowStart = index_start(masterRow);
//     int rowEnd = index_end(masterRow);
//     assert(is_indxInbound(index, rowStart, rowEnd) == true);

//     int index2 = OUTBOUND_END;
//     int masterRow2 = kth_row(index2);
//     int rowStart2 = index_start(masterRow2);
//     int rowEnd2 = index_end(masterRow2);
//     assert(is_indxInbound(index2, rowStart2, rowEnd2) == true);
// }

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
    assert(index_start(BSA_ROWS - 1) == MAXSTART_INDEX); //last row 29
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
    assert(index_end(BSA_ROWS - 1) == MAXEND_INDEX);
}

// void test_krow(void){
//     int k;
//     k = 0;
//     assert(kth_row(0, &k) == 0);
//     k = 0;
//     assert(kth_row(1, &k) == 1);
//     k = 0;
//     assert(kth_row(2, &k) == 1);
//     k = 0;
//     assert(kth_row(3, &k) == 2);//works now
//     k = 0;
//     assert(kth_row(6, &k) == 2); 
//     k = 0;
//     assert(kth_row(7, &k) == 3); 
//     k = 0;
//     assert(kth_row(14, &k) == 3);
//     k = 0;
//     assert(kth_row(30, &k) == 4); 
//     k = 0;
//     assert(kth_row(128, &k) == 7);
// }


bool testK(int k){ //works
    if ((k < 0) || (k >= BSA_ROWS)){
        return false;
    }
    return true;
}

void test_testK(void){ //works
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
    for (int y = 0; y < BSA_ROWS; y++){ //rename 
        if (b->master[y]->child != NULL){
            for (int x = 0; x < b->master[y]->rowLen; x++){
                if (b->master[y]->child[x] == indx){
                    return &(b->master[y]->child[x]);
                }
            }
        }
    }
    return NULL;
}

// Delete element at index indx - forces a shrink
// if that was the only cell in the row occupied.
bool bsa_delete(bsa* b, int indx){ //del after: use free function for delete. Delete row if nothing is set
    return false;
    if (b->master != NULL){
        printf("%d", indx);
    }
    return true;
}

// Returns maximum index written to so far or
// -1 if no cells have been written to yet
int bsa_maxindex(bsa* b){
    //base case (-1): does b->array.positionIndex == NULL? return
    if ((b == NULL) || (b->master == NULL)){
        return OUTBOUND;
    }
    int maxIndex = OUTBOUND;
    //loop through, calling kendindex to kstart, stopping at where a value != 0. have to call k fnctions then. easier way?
    for (int y = 0; y < BSA_ROWS; y++){
        if (b->master[y]->child != NULL){
            for (int x = 0; x < b->master[y]->rowLen; x++){
                if ((b->master[y]->child[x] != 0) && x > maxIndex){
                    maxIndex = x;
                }
            }
        }
    }
    return maxIndex;
}

// Clears up all space used
bool bsa_free(bsa* b){
    //if b has been allocated space (!= NULL), then clear. if == NULL return false? check driver.c
    //first false
    if (b->master == NULL){
        printf("Does not need to be freed!"); //remove after
        return false;
    }
    for (int k = 0; k < BSA_ROWS; k++){
        if (b->master[k]->child != NULL){
            free(b->master[k]->child);
        }
    }
    free(b->master);
    free(b);
    printf("freed\n");
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
