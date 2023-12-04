#include "specific.h"

bsa* bsa_init(void){ //need conditional for if ==NULL
    bsa* buildBSA = (bsa*) calloc(1, sizeof(bsa)); //created bsaCOL
    if (buildBSA == NULL){
        return NULL; //just return?
    }
    buildBSA->array = (BSA_Col*)calloc(BSA_ROWS, sizeof(BSA_Col * BSA_ROWS)); //do i need if (build BSA != NULL?)
    if (buildBSA->array == NULL){
        return false;
    }
    return buildBSA;
}

// Set element at index indx (2^k) with value d i.e. b[i] = d;
// May require an allocation if it's the first element in that row
bool bsa_set(bsa* b, int indx, int d){
    //Check that b has been initialised first as NULL return false indicates bsa allocation did not work
    if (indx >= (MAXEND_INDEX + 1) || (indx < 0)){
        return false;
    } 
    if (testInitialisation(b) == false){
        return false;
    } //works
    //first calculating kth row given the index
    int tempK = 0;
    int k = kth_row(indx, &tempK); //k to be 2
    //Check that kth row is in bound, false if 30 or higher
    if (testK(k) == false){
        return false;
    }
    if (storeData(b, k) == false){
        return false;
    }
    //set value d into the created row - keep here
    int position = indx - b->array[k].kStart;
    b->array[k].positionIndex[position] = d;
    return true;
}

bool storeData(bsa* b, int k){
    if ((testInitialisation(b) || testK(k)) == false){
        return false;
    }
    b->array->kStart = index_start(k);
    b->array->kEnd = index_end(k); 
    b->array->rowLen = (b->array->kEnd - b->array->kStart) + 1; //function? - want to make 4 - works!

    if (b->array[k].positionIndex == NULL){ //yessss
        b->array[k].positionIndex = calloc(b->array->rowLen, sizeof(int));
        if (b->array[k].positionIndex == NULL){
            return false;
        }
        for (int i = 0; i < b->array->rowLen; i++){
            b->array[k].positionIndex[i] = 0;
        }
    }
    return true;
}

void test_krowNew(void){ //works
    int k;
    k = 0;
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

int kth_row(int index, int *k){ //pass b too?
    int iS = index_start(*k); //works
    int iE = index_end(*k);

    if((index >= iS) && (index <= iE)){
        return *k;
    }
    else{
        *k += 1;
        return kth_row(index, k);
    }
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

void test_krow(void){
    int k;
    k = 0;
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

bool testInitialisation(bsa *b){
    if (b == NULL || b->array == NULL){
        return false;
    }
    return true;
}

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

void testInit(void){
    bsa *noAlloc = NULL;
    assert(testInitialisation(noAlloc) == false);

    bsa *allocated = bsa_init();
    assert(testInitialisation(allocated) == true);
    bsa_free(allocated);
}
// Return pointer to data at element b[i]
// or NULL if element is unset, or part of a row that hasn't been allocated.
int* bsa_get(bsa* b, int indx){ 
    return false;     
    b->array = calloc(BSA_ROWS, sizeof(BSA_Col));
    if (b->array != NULL){
        printf("%d", indx);
    }
    return false;
}

// Delete element at index indx - forces a shrink
// if that was the only cell in the row occupied.
bool bsa_delete(bsa* b, int indx){ //del after: use free function for delete. Delete row if nothing is set
    return false;
    if (b->array != NULL){
        printf("%d", indx);
    }
    return true;
}

// Returns maximum index written to so far or
// -1 if no cells have been written to yet
int bsa_maxindex(bsa* b){
    //base case (-1): does b->array.positionIndex == NULL? return
    if (b->array->positionIndex == NULL){
        return 1;
    }
    //loop through, calling kendindex to kstart, stopping at where a value != 0. have to call k fnctions then. easier way?
    int endB = sizeof(&b->array->positionIndex) / sizeof(b->array->positionIndex[0]) - 1;
    if (b->array->positionIndex[endB] == 0){
        endB--;
        return bsa_maxindex(b);
    }
    return 0;
}

// Clears up all space used
bool bsa_free(bsa* b){
    //if b has been allocated space (!= NULL), then clear. if == NULL return false? check driver.c
    //first false
    if (b->array == NULL || b->array->positionIndex == NULL){
        printf("Does not need to be freed!"); //remove after
        return false;
    }
    else{
        free(b->array->positionIndex);
        free(b->array);
        free(b);
    }
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

    test_krow();
    testIstart();
    testIend();
    
    test_testK();

    // bsa_set2(testArray, (MAXEND_INDEX + 1), 10);    
}
