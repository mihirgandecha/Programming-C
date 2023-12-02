#include "specific.h"

bsa* bsa_init(void){
    bsa* buildBSA = (bsa*) calloc(1, sizeof(bsa)); //created bsaCOL
    buildBSA->array = calloc(BSA_ROWS, sizeof(BSA_Col)); //do i need if (build BSA != NULL?)

    return buildBSA;
}

// Set element at index indx (2^k) with value d i.e. b[i] = d;
// May require an allocation if it's the first element in that row
bool bsa_set(bsa* b, int indx, int d){
    //Check that b has been initialised first (it needs to be passed through to bsa_init first). if statement for if not null, call bsa_init? <- check driver.c
    if (b == NULL || b->array == NULL){
        return false;
    }
    //first calculating kth row given the index

    int k = 0;
    int kRow = kth_row(indx, &k);

    //Check that kth row is in bound, false if 30 or higher
    if (kRow >= BSA_ROWS){
        return false;
    }
    //might need to redo how kth_row works as this calls again (more memory) - calculating array row size, given index
    //example: row(k) = 2; index-6, d=10
    int kRowStart = index_start(kRow); //output 3
    int kRowEnd = index_end(kRow); //output 6 - works
    //row size should be 4
    int rowSize = (kRowEnd - kRowStart) + 1; //function? - want to make 4
    //check if row (2nd) at k has been created
    if (b->array[k].positionIndex == NULL){
        //create the row with the required size
        b->array[k].positionIndex = malloc(sizeof(int) * rowSize);
        //check this works^
        if (b->array[k].positionIndex == NULL){
            return false;
        }
        //initialise the row with default values 'X'? or 0?
        for (int i = 0; i < rowSize; i++){
            b->array[k].positionIndex[i] = 0;
        }
    }
    //set value d into the created row
    b->array[k].positionIndex[indx - kRowStart] = d;
    return true; //works i think
}

int kth_row(int index, int *k){

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
    assert(index_start(BSA_ROWS - 2) == 268435455); //row 28
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
        printf("does not need to be freed!"); //remove after
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
}
