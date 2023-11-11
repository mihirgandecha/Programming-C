
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define N 8
#define MAX_BOARD 10

typedef struct board {
    int chessboard [N];

} board;

int main(int argc, char* argv[]){
    if (argc != 2){
        fprint(stderr, "Usage: %s <filein> <fileout > \n", argv[0])
        exit(EXIT_FAILURE);
    }
    return 0;
}
    int f = 0; //representing position of boards, 0 being start