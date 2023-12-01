#include "specific.h"

bsa* bsa_init(void){
    bsa* buildBSA = (bsa*) calloc(1, sizeof(bsa)); //created bsaCOL
    buildBSA->array = calloc(BSA_ROWS, sizeof(BSA_Col));

    return buildBSA;
}

// Set element at index indx (2^k) with value d i.e. b[i] = d;
// May require an allocation if it's the first element in that row
bool bsa_set(bsa* b, int indx, int d){
    //first calculating kth row given the index 
    int k = 0;
    kth_row(indx, &k);
    
    if (k < BSA_ROWS){
        return true;
    }
    
    if (b->array != NULL){
        index_end(d);
    }
    return false;
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
    long result = 1L << k; 
    return result - 1;
}

int index_end(int k){
    if (k == 0){
        return 0;
    }
    return (1L << (k + 1)) - 2;
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
    assert(kth_row(3, &k) == 2); //works now
    
    k = 0;
    assert(kth_row(6, &k) == 2); //works now
    
    k = 0;
    assert(kth_row(7, &k) == 3); //works now

    k = 0;
    assert(kth_row(14, &k) == 3);

    k = 0;
    assert(kth_row(15, &k) == 4);
    
    k = 0;
    assert(kth_row(17, &k) == 4);
    
    k = 0;
    assert(kth_row(30, &k) == 4); 

    k = 0;
    assert(kth_row(32, &k) == 5); 

    k = 0;
    assert(kth_row(45, &k) == 5);

    k = 0;
    assert(kth_row(63, &k) == 6);

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
bool bsa_delete(bsa* b, int indx){
    return false;
    if (b->array != NULL){
        printf("%d", indx);
    }
    return true;
}

// Returns maximum index written to so far or
// -1 if no cells have been written to yet
int bsa_maxindex(bsa* b){
    return false;
    if (b->array != NULL){
        printf("hi");
    }
    return true;
}

// Clears up all space used
bool bsa_free(bsa* b){
    free(b);
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
}
