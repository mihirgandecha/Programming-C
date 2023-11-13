
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_BOARD 10

typedef struct board {
    int *chessboard;
} board;

void parentBoard(board* b, int n){
    b->chessboard = (int*)malloc(n* sizeof(int));
    if (b->chessboard == NULL){
        fprintf(stderr, "Failed to dynamically allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++){
        b->chessboard[i] = -1;
    }
}

void freeMemory(board *b){
    free(b->chessboard);
}

// int main(int argc, char* argv[]){
    int main(void){
    // if (argc != 2){
    //     fprint(stderr, "Usage: %s <filein> <fileout > \n", argv[0])
    //     exit(EXIT_FAILURE);
    // }
    int n = 3;
    board myBoard;
    parentBoard(&myBoard, n);

    freeMemory(&myBoard);

    return 0;
    }
//     int f = 0; //representing position of boards, 0 being start

// void test(void){
//     assert()
// }
