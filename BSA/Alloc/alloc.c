#include "specific.h"

bsa* bsa_init(void){
    bsa* buildBSA = (bsa*) calloc(1, sizeof(bsa)); //created bsaCOL
    buildBSA->array = calloc(BSA_ROWS, sizeof(BSA_Col));

    return buildBSA;
}

// Set element at index indx (2^k) with value d i.e. b[i] = d;
// May require an allocation if it's the first element in that row
bool bsa_set(bsa* b, int indx, int d){
    return false;
    printf("%d %d %d", b, indx, d);
}
// Set some values
//    assert(bsa_set(b, 0, 4)); //index-0 to value 4
//    assert(bsa_maxindex(b)==0);
//    // Reset existing value
//    assert(bsa_set(b, 0, 0)); //overwriting and resetting to 0
//    assert(bsa_set(b, 15, 15)); //now setting to 15


// Return pointer to data at element b[i]
// or NULL if element is unset, or part of a row that hasn't been allocated.
int* bsa_get(bsa* b, int indx){
    return false;
    printf("%d %d", b, indx);
}

// Delete element at index indx - forces a shrink
// if that was the only cell in the row occupied.
bool bsa_delete(bsa* b, int indx){
    return false;
    printf("%d %d", b, indx);
}

// Returns maximum index written to so far or
// -1 if no cells have been written to yet
int bsa_maxindex(bsa* b){
    return false;
    printf("%d", b);
}

// Returns stringified version of structure
// Each row has its elements printed between {}, up to the maximum index.
// Rows after the maximum index are ignored.
bool bsa_tostring(bsa* b, char* str){
    return false;
    printf("%d %s", b, str);
}

// Clears up all space used
bool bsa_free(bsa* b){
    free(b);
    return;
}

// Allow a user-defined function to be applied to each (valid) value 
// in the array. The user defined 'func' is passed a pointer to an int,
// and maintains an accumulator of the result where required.
void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc){
    return;
    if (func != NULL) {
        func(&b->numRows, acc); 
    }
}

// You'll this to test the other functions you write
void test(void){
    bsa* testArray = bsa_init();
    for (int testcolP = 0; i < BSA_ROWS; testcolP++){
        assert(testArray->col[testcolP] == NULL);
        
    }
    free(testArray);
}
