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

bool bsa_set(bsa* b, int indx, int d){
    //Check that b has been initialised first as NULL return false indicates bsa allocation did not work 
    testInitialisation(b);

    //first calculating kth row given the index
    int k = kthRow_Main(indx);
    //invalid indx if OUTBOUND
    if (k == OUTBOUND){
        return false;
    }
    //rest of func...
    return true;
}
//working version:
bool bsa_set(bsa* b, int indx, int d){
    //Check that b has been initialised first as NULL return false indicates bsa allocation did not work 
    testInitialisation(b);

    int k = kthRow_Main(indx);


    //first calculating kth row given the index
    int tempK = 0;
    int k = kth_row(indx, &tempK);
    //Check that kth row is in bound, false if 30 or higher
    if (k >= BSA_ROWS){
        return false;
    }
    //Calculate and return measurements dataset:

    //might need to redo how kth_row works as this calls again (more memory) - calculating array row size, given index
    //example: row(k) = 2; index-6, d=10

    int kRowStart = index_start(k); //output 3
    int kRowEnd = index_end(k); //output 6 - works
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
    b->array[k].positionIndex[indx - kRowStart] = d; //consider putting in struct
    return true; //works i think
}

    int k = kthRow_Main(indx);

void kthRow_Helper(int indx, int *k){
    if (*k >= BSA_ROWS){
        return;
    }
    int iS = index_start(*k); //works
    int iE = index_end(*k);
    if(!(indx >= iS) && (indx <= iE)){
        *k += 1;
        kthRow_Helper(indx, k);
    }
}

int kthRow_Main(int indx){
    int k = 0;
    kthRow_Helper(indx, &k);

    if (k >= BSA_ROWS){
        return OUTBOUND;
    }
    return k;
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