#include "8q.h"
//main function to take arguement and cmnd-line number of arguements (as an array)
int main(int argc, char *argv[]){

    int n = MAX_BOARD;
    //initialise to see if program uses-which it should!!! in makefile or cmnd line ask in labs!?
    bool verbose = false;
    
    if (argc < 2 || argc > 3){
        fprintf(stderr, "Usage: %s <fileout>\n", argv[0]);
        return EXIT_FAILURE;
    }
    //make sure n is a number and is in range
    if (sscanf(argv[1], "%d", &n) != 1 || n <= 0 || n > MAX_BOARD){
        fprintf(stderr, "Invalid board size");
        return EXIT_FAILURE;
    }
    //making sure that there are three arguements and that the third is verbose
    if (argc == 3 && strcmp(argv[2], "verbose") == 0){
        verbose = true;
    }
    //breadth-first search implementation:
    //Initialise the array list of structures for 4(N) board to solve
    board solve_list[MAX_PERM];
    //f representing front of queue and b representing back of queue
    int f = 0;
    int b = 1; 
    
    board parentBoard;
    emptyBoard(&parentBoard, n);
    solve_list[f] = parentBoard;

    board childBoard;
    deepCopy(&solve_list[f], &childBoard, n);
    solve_list[b] = childBoard;

    printBoard(&solve_list[b], n);
    printf("\n");

    //place q1
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            solve_list[b].chessboard[i][j] = QUEEN;
            b++;
        }
    }

    printBoard(&solve_list[b], n);
    //test generate such that placing Q1 on a board is always N*N
   

    //Check in-bound?
    // in_bound(&parent_board, n);

    //do-while loop to represent childBoards being generated whilst f!=childBoard
    // do{
    //     generate_childBoards();
    //     f++;
    // }
    // while(f != end_childBoard);
    // printf(solutions);
    
    test();
    return 0;

    return 0;

}
void emptyBoard(board *b, int board_size){
    for (int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            b->chessboard[i][j] = EMPTY;
        }
    }
}

void printBoard(board *b, int board_size){
    for (int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            printf("%c", b->chessboard[i][j]);
        }
        printf("\n");
    }
}
   

void deepCopy(board *original, board *copy, int board_size){
    for (int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            copy->chessboard[i][j] = original->chessboard[i][j];
        }
    }
}

bool in_bound(int row, int col, int board_size){
    return row >= && row < board_size && col >= 0 && col < board_size;
}

//check if a queen is safe in a column or row
bool isSafe_RC(board *b, int board_size, int row, int col){
    int queen_count = 0;
    
    for (int i = 0; i < board_size; i++){
        if (b->chessboard[row][i] == QUEEN || b->chessboard[i][col] == QUEEN){
            queen_count++;
            if (queen_count > 1){
                return false;
            }
        }
    }
    return true;
}
//Function to check if one queen is safe for any diagonal direction
bool Q_DiagSafe(board b*, int Q_Row, int Q_Col, int B_Row, int B_Col, int board_size){
    int row_current = Q_Row + B_Row;
    int col_current = Q_Col + B_Col;

    //Testing for if Q is safe in its current 
    while(in_bound(row_current, col_current, board_size)){
        if(b->chessboard[row_current][col_current] != QUEEN){
            return false;
        }
        row_current = row_current + B_Row;
        col_current = col_current + B_Col;
    }
    return true; 
}
//Function to check if all N queens are safe, using Q_DiagSafe to check each Queen 
bool QAll_DiagSafe(board *b, int board_size){
    for (int row = 0; row < board_size; row++){
        for (int col = 0; col < board_size; col++){
            if (b->chessboard[row][col] == QUEEN){
                if (!Q_DiagSafe(b, row, col, -1, -1, board_size) ||
                    !Q_DiagSafe(b, row, col, -1,  1, board_size) ||
                    !Q_DiagSafe(b, row, col,  1, -1, board_size) ||
                    !Q_DiagSafe(b, row, col,  1,  1, board_size)) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool isSafe(board *b, int board_size, int row, int col) {
    // Check row and column safety
    if (!isSafe_RC(b, board_size, row, col)) {
        return false;
    }
    // Check diagonal safety
    if (!Q_DiagSafe(b, row, col, -1, -1, board_size) ||
        !Q_DiagSafe(b, row, col, -1,  1, board_size) ||
        !Q_DiagSafe(b, row, col,  1, -1, board_size) ||
        !Q_DiagSafe(b, row, col,  1,  1, board_size)) {
        return false;
    }
    return true;
}

void test(void){
    assert(1+1 == 2);
}
