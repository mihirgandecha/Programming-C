#include "8q.h"

int main(int argc, char *argv[]){
    int n = MAX_BOARD;
    board t;
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
    printf("%2d\n",parentBoard(&t, n));
    
    
    //For 3x3 board there should be 9 childboards
    // int childb_number = n * n;
    // int queens = n;

    // board solution[n] = {
    //     {}
    // }
    return 0;
}


int parentBoard(board *b, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b->chessboard[i][j] = EMPTY;
        }
    }
    
}

