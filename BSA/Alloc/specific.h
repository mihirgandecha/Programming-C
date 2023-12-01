#pragma once

#include "../bsa.h"

struct BSA_Col{
    int* positionIndex; //the position of d within a row created 
};

struct bsa {
    BSA_Col* array; //whole bsa struct, what pnter-index within pointer of array
};
