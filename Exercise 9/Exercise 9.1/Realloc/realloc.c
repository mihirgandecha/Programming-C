#include "arr.h"
#include "specific.h"

/* Creates the empty array */
arr* arr_init(void){
    arr* a = (arr*)ncalloc(1, sizeof(int));
    
    return a;
// a = arr_init();
//    assert(a != NULL);

}
/* Similar to l[n] = i, safely resizing if required */
void arr_set(arr *l, int n, int i);
/* Similar to = l[n] */
int arr_get(arr *l, int n);
/* Clears all space used, and sets pointer to NULL */
void arr_free(arr **l);
