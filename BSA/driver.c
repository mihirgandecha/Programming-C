#include "bsa.h"

#define LISTSTRLEN 1000

void times(int* p, int* n);
void twice(int* p, int* n);

int main(void)
{

   test();
   // char str[LISTSTRLEN] = "";

   // A NULL BSA has size zero
   // assert(bsa_maxindex(NULL)==-1); //no room to put anything else
   // assert(!bsa_tostring(NULL, str));

   // Initialise
   bsa* b = bsa_init(); //initialising BSA (1D arr of 30 - yet no rows are initialised)
   assert(b);
   bsa_free(b);
   bsa_set(b, 3, 10);

   // assert(bsa_maxindex(b)==-1); //max_index is what you get from it, -1 because we cant get anything and we have no index

   // Set some values
//    assert(bsa_set(b, 0, 4)); //index-0 to value 4
//    assert(bsa_maxindex(b)==0);
//    // Reset existing value
//    assert(bsa_set(b, 0, 0)); //overwriting and resetting to 0
//    assert(bsa_set(b, 15, 15)); //now setting to 15

//    // tostring
//    assert(bsa_tostring(b, str));
//    assert(strcmp(str, "{[0]=0}{}{}{}{[15]=15}")==0); //curly braces is each row, {} means empty row, meaning only go up to row we have allocated
// //maybe call maxindex here^
// //{[15]=15}" row 15 = value 15
//    // Get some values tbsa've already been set
//    int* p = bsa_get(b, 0);
//    assert(p);
//    assert(*p == 0);
//    p = bsa_get(b, 15);
//    assert(p);
//    assert(*p == 15);

//    // Get an unset value 
//    p = bsa_get(b, 1);
//    assert(!p);
//    p = bsa_get(b, 1024);
//    assert(!p);

//    // 
//    assert(bsa_set(b, 100, 100));
//    assert(bsa_maxindex(b)==100);
//    // Once resized, using a get is OK
//    p = bsa_get(b, 100);
//    assert(p);
//    assert(*p == 100);
//    // Retest values from BSA before resize
//    p = bsa_get(b, 15);
//    assert(p);
//    assert(*p == 15);

//    assert(bsa_tostring(b, str));
//    assert(strcmp(str, "{[0]=0}{}{}{}{[15]=15}{}{[100]=100}")==0);

//    // Let's do some deleting

//    // Cell not not used, can't delete it
//    assert(!bsa_delete(b, 99));
//    // Cell is used, can delete it
//    assert(bsa_delete(b, 100));
//    assert(bsa_maxindex(b)==15);
//    // Check it's gone
//    assert(bsa_tostring(b, str));
//    assert(strcmp(str, "{[0]=0}{}{}{}{[15]=15}")==0);
//    // Cell is used, can delete it
//    assert(bsa_delete(b, 15));
//    assert(bsa_maxindex(b)==0);
//    assert(bsa_tostring(b, str));
//    assert(strcmp(str, "{[0]=0}")==0);
//    // Delete last element left
//    assert(bsa_delete(b, 0));
//    assert(bsa_maxindex(b)<0);
//    assert(bsa_tostring(b, str));
//    assert(strcmp(str, "")==0);
  
//    bsa_free(b);

//    // foreach - use it to compute product of numbers, and also to double each one
//    b = bsa_init();
//    bsa_set(b, 1, 1);
//    bsa_set(b, 2, 2);
//    bsa_set(b, 3, 3);
//    int acc = 1;
//    bsa_foreach(times, b, &acc);
//    assert(acc==6);
//    // Double each numbers in array
//    assert(bsa_tostring(b, str));
//    assert(strcmp(str, "{}{[1]=1 [2]=2}{[3]=3}")==0);
//    bsa_foreach(twice, b, &acc);
//    assert(bsa_tostring(b, str));
//    assert(strcmp(str, "{}{[1]=2 [2]=4}{[3]=6}")==0);
//    bsa_free(b);

//    return 0;
// }

// void times(int* p, int* n)
// {
//    *n = *n * *p;
// }

// void twice(int* p, int* n)
// {
//    // Need to use n to switch off warnings :-(
//    *n = 0;
//    *p = *p * 2;
}
   
