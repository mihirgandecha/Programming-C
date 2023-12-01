#include "specific.h"

bsa* bsa_init(void){
    bsa* buildArray = (bsa*) calloc(1, sizeof(bsa)); 

    // for (int numRows = 0; i < BSA_ROWS; numRows++){
    //     buildArray->col == NULL;
    // }
    return buildArray;
}

// Set element at index indx with value d i.e. b[i] = d;
// May require an allocation if it's the first element in that row
bool bsa_set(bsa* b, int indx, int d){
    return false;
    printf("%d %d %d", b, indx, d);
}

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
    for (int i = 0; i < BSA_ROWS; i++){
        assert(testArray->numRows >= 0);
        assert(testArray->numRows <= 29);
        assert(testArray->row == NULL);
    }
    free(testArray);
}
