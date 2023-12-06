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
}bool testInitialisation(bsa *b){
    if (b == NULL || b->array == NULL){
        return false;
    }
    return true;
}

// Set element at index indx (2^k) with value d i.e. b[i] = d;
// May require an allocation if it's the first element in that row
// bool bsa_set(bsa* b, int indx, int d){
//     //Check that b has been initialised first as NULL return false indicates bsa allocation did not work 
//     if (testInitialisation(b) == false){
//         return false;
//     }
//     //first calculating kth row given the index
//     int tempK = 0;
//     int k = kth_row(indx, &tempK);
//     //Check that kth row is in bound, false if 30 or higher
//     if (k >= BSA_ROWS){
//         return false;
//     }
//     //Calculate and return measurements dataset:
//     b->array->kStart = index_start(k); //output 3
//     b->array->kEnd = index_end(k); //output 6 - works
//     //row size should be 4
//     b->array->rowLen = (b->array->kEnd - b->array->kStart) + 1; //function? - want to make 4
//     //check if row (2nd) at k has been created
//     if (b->array[k].positionIndex == NULL){
//         //create the row with the required size
//         b->array[k].positionIndex = calloc(b->array->rowLen, sizeof(int));
//         //check this works^
//         if (b->array[k].positionIndex == NULL){
//             return false;
//         }
//         //initialise the row with default values 'X'? or 0?
//         for (int i = 0; i < b->array->rowLen; i++){
//             b->array[k].positionIndex[i] = 0;
//         }
//     }
//     //set value d into the created row - keep here
//     b->array[k].positionIndex[indx - b->array->kStart] = d;
//     return true; //works i think
// }

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


// int kth_row(int index, int *k){ 
//     int iS = index_start(index); //works
//     int iE = index_end(index);

//     if((index >= iS) && (index <= iE)){
//         return *k;
//     }
//     else{
//         index += 1;
//         return kth_row(index, k);
//     }
// }

// void assert_firstInit(void){
//     bsa *noAlloc = OUTBOUND;
//     assert(test_firstInit(noAlloc) == false);

//     bsa *allocated = bsa_init();
//     assert(test_firstInit(allocated) == true);
//     bsa_free(allocated);
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

// bsa* initialiseOp1(void){
//     bsa* bsaOp1 = bsa_init();
//     // bool result = test_firstInit(bsaOp1);

//     if (bsaOp1 == NULL){ //do i need to do this again?
//         return NULL;
//     }
//     if ((bsaOp1->ops == NULL) || (bsaOp1->ops->test_firstInit == NULL)){
//         //QLab: messing up order if freeing?
//         free(bsaOp1);
//         return NULL;
//     }
//     bool isInitSuccessful = bsaOp1->ops->test_firstInit(bsaOp1);
//         if(!isInitSuccessful){
//             //op1 was not successful and so not stored - free
//             free(bsaOp1->ops);
//             free(bsaOp1);
//             return NULL;
//         }
//     //LabsQ: so it now means that bsa HAS TO BE initalised FIRST ALWAYS!!!
//     return bsaOp1;
// }
