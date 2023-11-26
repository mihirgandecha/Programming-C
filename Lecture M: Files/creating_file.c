/* Creates a file called helloworld.txt
in the current filespace and writes to it */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Clobber the file if it exists already
    FILE* fp = fopen("helloworld.txt", "w");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open file?\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "Hello World!\n");
    // fscanf() is also available to read in
    fclose(fp);
    return EXIT_SUCCESS;
}

void placeFirstQueen(board *solve_list, int *b, int board_size) {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            board newBoard;
            emptyBoard(&newBoard, board_size);  
            newBoard.chessboard[i][j] = QUEEN;  
            solve_list[*b] = newBoard;          
            (*b)++;                             
        }
    }
}

