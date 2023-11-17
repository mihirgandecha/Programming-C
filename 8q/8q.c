#include "8q.h"

int main(int argc, char *argv[]){
    int n = MAX_BOARD;
    bool verbose = false;
    
    if (argc < 2 || argc > 3){
        fprintf(stderr, "Usage: %s <fileout>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    if (sscanf(argv[1], "%d", &n) != 1 || n <= 0 || n > MAX_BOARD){
        fprintf(stderr, "Invalid board size");
        return EXIT_FAILURE;
    }
    
    if (argc == 3 && strcmp(argv[2], "verbose") == 0){
        verbose = true;
    }

    board solve_list[MAX_PERM];
    int b = 0;
    int solutions = 0;
    
    initialise_Q1boards(solve_list, &b, n);
    solveBoard(solve_list, &b, &solutions, n, &verbose);
    
    return EXIT_SUCCESS;
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

int in_bound(int row, int col, int board_size){
    if (row >= 0 && row < board_size && col >= 0 && col < board_size){
        return 0;
    }
    return 1;
}

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

bool Q_DiagSafe(board *b, int row, int col, int board_size){
    int directions[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    
    for (int i = 0; i < 4; i++) {
        int dRow = directions[i][0];
        int dCol = directions[i][1];

        int cRow = row, cCol = col;
        while (cRow >= 0 && cRow < board_size && cCol >= 0 && cCol < board_size) {
            if (cRow != row && cCol != col && b->chessboard[cRow][cCol] == QUEEN) {
                return false;
            }
            cRow += dRow;
            cCol += dCol;
        }
    }
    return true;
}

bool isSafe(board *b, int board_size, int row, int col) {
    if (!isSafe_RC(b, board_size, row, col)) {
        return false;
    }

    if (!Q_DiagSafe(b, row, col, board_size)) {
        return false;
    }

    return true;
}

void initialise_Q1boards(board *solve_list, int *b, int board_size){
    for (int j = 0; j < board_size; j++) {
        board childBoard;
        emptyBoard(&childBoard, board_size);
        childBoard.chessboard[0][j] = QUEEN;  
        solve_list[*b] = childBoard;          
        (*b)++;         
    }
}

void addQN(board *current_board, board *solve_list, int board_size, int *b) {
    int nextRow = -1;
    for (int i = 0; i < board_size && nextRow == -1; i++) {
        bool rowEmpty = true;
        for (int j = 0; j < board_size; j++) {
            if (current_board->chessboard[i][j] == QUEEN) {
                rowEmpty = false;
            }
        }
        if (rowEmpty) {
            nextRow = i;
        }
    }

    if (nextRow != -1) {
        for (int col = 0; col < board_size; col++) {
            if (isSafe(current_board, board_size, nextRow, col)) {
                board childBoard;
                deepCopy(current_board, &childBoard, board_size);
                childBoard.chessboard[nextRow][col] = QUEEN;

                if (*b < MAX_PERM) {
                    solve_list[*b] = childBoard;
                    (*b)++;
                } else {
                    return;
                }
            }
        }
    }
}

void solveBoard(board *solve_list, int *b, int *solutions, int board_size, bool *verbose) {
    int current_index = 0;

    while (current_index < *b) {
        if (isQNSolved(&solve_list[current_index], board_size)) {
            (*solutions)++;
            if (*verbose) {
                printBoardSolution(&solve_list[current_index], board_size);
            }
        } else {
            addQN(&solve_list[current_index], solve_list, board_size, b);
        }
        current_index++;
    }
    printf("Total solutions: %d\n", *solutions);
}

bool isQNSolved(board *b, int board_size){
    int queen_count = 0;
    for (int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            if (b->chessboard[i][j] == QUEEN){
                queen_count++;
                if (!isSafe(b, board_size, i, j)){
                    return false;
                }
            }
        }
    }
    if(queen_count != board_size){
        return false;
    }
    return true;
}

void printBoardSolution(board *b, int board_size){
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (b->chessboard[i][j] == QUEEN) {
                printf("%d", j + 1);
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool areBoardsIdentical(board *board1, board *board2, int board_size) {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (board1->chessboard[i][j] != board2->chessboard[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool compareBoard(board *current_board, board solve_list[], int num_boards, int board_size) {
    for (int b = 0; b < num_boards; b++) {
        if (areBoardsIdentical(current_board, &solve_list[b], board_size)) {
            return true;
        }
    }
    return false;
}

void test(void){
    int n = 3;
    board solve_list[MAX_PERM];
    int b = 0;

    initialise_Q1boards(solve_list, &b, n);
    assert(b == n * n);
}
