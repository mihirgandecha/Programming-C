#include "8q.h"

int main(int argc, char *argv[]){
    int n = MAX_BOARD;
    board parent_board;
    bool verbose = false;

    if (argc < 2 || argc > 3){
        fprintf(stderr, "Usage: %s <size> [verbose]\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    n = atoi(argv[1]);
    if (n <= 0 || n > MAX_BOARD){
        fprintf(stderr, "Invalid board size");
        return EXIT_FAILURE;
    }

    if (argc == 3 && strcmp(argv[2], "verbose") == 0){
        verbose = true;
    }

    *parent_board->queen_count = n; 
    
    //For 3x3 board there should be 9 childboards
    // int childb_number = n * n;
    // int queens = n;

    // board solution[n] = {
    //     {}
    // }
    return 0;
}

char isSafecr(board childBoard, *parentBoard, int n, int queen_count){

    //For a 4x4 board:
    assert(isSafecr(childBoard1, *parentBoard, int 4, int 4) == 2031, count_child == 1);
    assert(childBoard1.quenn_count == 4);
    assert(childBoard1.empty_count == 12);
    //Squares to be filled = n*n, make sure empty+queen = n*n
    assert(childBoard1.queen_count + childBoard1.empty_count = n*n);



    int f[0] = *parentBoard;
    //Make into assert test?
    *parentBoard.nposib = n*n;
    *parentBoard.quenn_count = n;
    *parentBoard.empty_count = *parentBoard.nposib - *parentBoard.queen_count;
    
    //For row, first placement:
    



    //Output: childBoard -> increase counter, output solution of where Q is along j as 1-D Arr

    return 0;
}


void emptyBoard(board *b, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b->chessboard[i][j] = EMPTY;
        }
    }
    
}

char printBoard(board *c, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%c", c->chessboard);
        }
    }
    return 0;
}
