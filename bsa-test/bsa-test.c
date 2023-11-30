#include "bsatest.h"

int main(void)
{
   // Initialise
   bsa* b = bsa_init(); //initialising BSA (1D arr of 30 - yet no rows are initialised)
   assert(b);
   test();

}

bsa* bsa_init(void){
    bsa* buildArray = (bsa*) calloc(BSA_ROWS, sizeof(bsa)); 

    for (int i = 0; i < BSA_ROWS; i++){
        buildArray[i].numRows = i;
        buildArray[i].row = NULL;
    }
    return buildArray;
}

bool bsa_set(bsa* b, int indx, int d){

}

void test(void){
    bsa* testArray = bsa_init();
    for (int i = 0; i < BSA_ROWS; i++){
        assert(testArray->numRows >= 0);
        assert(testArray->numRows <= 29);
        assert(testArray->row == NULL);
    }
}
