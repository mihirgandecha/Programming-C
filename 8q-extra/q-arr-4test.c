#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_BOARD 10

//Write a solution for NQueen problem for 4x4
typedef struct queen_array {
    int n;
    char queen[MAX_BOARD];
    int q_index[MAX_BOARD];
} queen_array;

void q_arr(queen_array *t, int board_size);
void test(void);

int main(void) {

    //assert(q_arr(queen_array *a, 5) == {'Q','Q','Q','Q','Q'}, {1, 2, 3, 4, 5});
    int size = 4;

    queen_array four;
    q_arr(&four, size);

    // Print the arrays - remove
    printf("n is: %i\n", four.n);
    printf("Queens: ");
    for (int i = 0; i < size; i++) {
        printf("%c ", four.queen[i]);
    }
    printf("\nIndexes: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", four.q_index[i]);
    }
    printf("\n");
    test();
    return 0;
}

void q_arr(queen_array *t, int board_size){
    
    t->n = board_size;
    
    for (int i = 0; i < board_size; i++) {
        t->queen[i] = 'Q';      
        t->q_index[i] = i + 1;  
    }
}

void test(void){
    queen_array six;
    q_arr(&six, 6);
    
    assert(six.n == 6);
    assert(six.q_index[0] == 1 && six.q_index[5] == 6);
    

}
