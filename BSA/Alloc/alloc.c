#include "bsa.h"
#include "specific.h"

bsa* bsa_init(void){
    bsa* buildArray = (bsa*) calloc(BSA_ROWS, sizeof(bsa)); 

    for (int i = 0; i < BSA_ROWS; i++){
        buildArray[i].numRows = i;
        buildArray[i].row = NULL;
    }
    return buildArray;
}


// void test(void){
    
//     array1D* testInit = bsa_init();
//     assert(testInit == NULL);
//     }

