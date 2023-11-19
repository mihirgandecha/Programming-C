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
    //works
    board parentBoard;
    board solve_list[MAX_PERM];
    
    emptyBoard(&parentBoard, n);
    //Now parentBoard filled with X for n intput
    int f = 0;
    solve_list[f] = parentBoard;
    //Now parentBoard is set to f = 0, in array of struct list

    int list_size = 0;
    //Acts like back
    board initialBoard;
    emptyBoard(&initialBoard, n);

    testin_bound();
    test_isSafeRC();
    test_QDiagSafe();
    test_isSafe();

    
    // Solve the N-Queens problem

    if (verbose) {
        int solution_count = 0;
        nqueenSolved(solve_list, &list_size, &n);
        for (int i = 0; i < list_size; i++) {
            if (countQueens(&solve_list[i], n) == n) {
                solution_count++;
                printf("Solution %d:\n", solution_count);
                printBoardSolution(&solve_list[i], n);
            }
        }
        printf("%d solutions\n", solution_count);
    }

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

void deepCopy(board *original, board *copy, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            copy->chessboard[i][j] = original->chessboard[i][j];
        }
    }
}

void printAllBoards(board arrayof_struct[], int *n, int list_size){
    for (int i = 0; i < *n; i++){
        for (int j = 0; j < *n; j++){
            printf("%c", arrayof_struct[list_size].chessboard[i][j]);
        }
        printf("\n");
    }
}

//Check for queen functions:

int in_bound(int row, int col, int board_size){
    if (row >= 0 && row < board_size && col >= 0 && col < board_size){
        return IN_BOUND;
    }
    return OUT_BOUNDS;
}

void testin_bound(void){
    int board_size = MAX_BOARD;

    //test board is within bounds
    assert(in_bound(0, 0, board_size) == IN_BOUND);
    assert(in_bound(9, 9, board_size) == IN_BOUND);
    assert(in_bound(7, 9, board_size) == IN_BOUND);

    //test boundries of col and row inside
    assert(in_bound(0, (board_size - 1), board_size) == IN_BOUND);
    assert(in_bound((board_size - 1), 0, board_size) == IN_BOUND);

    //test OUT_BOUND
    assert(in_bound(-1, 0, board_size) == OUT_BOUNDS);
    assert(in_bound(0, -1, board_size) == OUT_BOUNDS);
    assert(in_bound(0, 10, board_size) == OUT_BOUNDS);
    assert(in_bound(10, 0, board_size) == OUT_BOUNDS);
                 
}

bool isSafe_RC(board *b, int board_size, int row, int col){

    for (int i = 0; i < board_size; i++){
        if ((b->chessboard[row][i] == QUEEN && i != col) || 
            (b->chessboard[i][col] == QUEEN && i != row)){
            return false;

            }
        }
    return true;
}

void test_isSafeRC(void){
    int board_size = 5;
    board testBoard;
    emptyBoard(&testBoard, board_size);

    //test on empty board
    for (int row = 0; row < board_size; row++){
        for (int col = 0; col < board_size; col++){
            assert(isSafe_RC(&testBoard, board_size, row, col) == true);
        }
    }

    //test for unsafe
    testBoard.chessboard[0][4] = QUEEN;
    testBoard.chessboard[4][4] = QUEEN;
    
    assert(isSafe_RC(&testBoard, board_size, 1, 4) == false);
    assert(isSafe_RC(&testBoard, board_size, 3, 4) == false);

}

bool Q_DiagSafe(board *b, int row, int col, int board_size){
    for (int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            //conditional to find Q position on a board
            if (b->chessboard[i][j] == QUEEN){
                //Difference between 2 diag points
                int dx = col - j;
                int dy = row - i;

                if ((dx == dy) || (dx == -dy)){
                    return false;
                }
            }
        }
    }
    return true;
}

void test_QDiagSafe(void){
    int board_size = MAX_BOARD;
    board testBoard;
    emptyBoard(&testBoard, board_size);

    // 4 tests for each diaganol
    testBoard.chessboard[0][0] = QUEEN;
    assert(Q_DiagSafe(&testBoard, 9, 9, board_size) == false);
    testBoard.chessboard[0][9] = QUEEN;
    assert(Q_DiagSafe(&testBoard, 9, 0, board_size) == false);
    testBoard.chessboard[9][0] = QUEEN;
    assert(Q_DiagSafe(&testBoard, 0, 9, board_size) == false);
    testBoard.chessboard[9][9] = QUEEN;
    assert(Q_DiagSafe(&testBoard, 0, 0, board_size) == false);
    
    // Test positions diagonally relative to the queen
    board testBoard2;
    int board_size2 = 5;
    emptyBoard(&testBoard2, board_size2);
    testBoard.chessboard[2][2] = QUEEN;
    assert(Q_DiagSafe(&testBoard, 0, 1, board_size2) == true); // Diagonally unsafe
    assert(Q_DiagSafe(&testBoard, 0, 4, board_size2) == false);  // Diagonally safe
    assert(Q_DiagSafe(&testBoard, 4, 3, board_size2) == true);  // Diagonally safe
    assert(Q_DiagSafe(&testBoard, 1, 1, board_size2) == false);
    // Additional tests can be added for thoroughness
}

bool isSafe(board *temp, int board_size, int row, int col){

    if ((isSafe_RC(temp, board_size, row, col) && Q_DiagSafe(temp, row, col, board_size)) == false){
        return false;
    }

    return true;
}

void test_isSafe(void){
    int board_size = 5;
    board testBoard;
    emptyBoard(&testBoard, board_size);

    testBoard.chessboard[3][2] = QUEEN;
    testBoard.chessboard[4][4] = QUEEN;

    assert(isSafe(&testBoard, board_size, 0, 3) == true);
    assert(isSafe(&testBoard, board_size, 2, 4) == false); 
    assert(isSafe(&testBoard, board_size, 2, 2) == false); 
    assert(isSafe(&testBoard, board_size, 4, 3) == false); 
    assert(isSafe(&testBoard, board_size, 0, 3) == true); 
    assert(isSafe(&testBoard, board_size, 0, 1) == true); 
    assert(isSafe(&testBoard, board_size, 2, 0) == true); 

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

                if (*b < MAX_BOARD) {
                    solve_list[*b] = childBoard;
                    (*b)++;
                } else {
                    return;
                }
            }
        }
    }
}

// void appendList(board arrayof_struct[], int *list_size, int *board_size){
//     int isSafe_count = 0;

//     for (int row = 0; row < *board_size; row++){
//         for (int col = 0; col < *board_size; col++){

//             int tempBoardSize = *board_size;
//             board temp_carentBoard;
            
//             emptyBoard(&temp_carentBoard, tempBoardSize);
//             printf("%d\n", *list_size);

//             if(isSafe(&temp_carentBoard, *board_size, row, col) == true){
//                 printf("Q is safe to place.");
//                 printf("\n\n");
//                 temp_carentBoard.chessboard[row][col] = QUEEN;
//                 arrayof_struct[*list_size] = temp_carentBoard;
//                 printAllBoards(arrayof_struct, board_size, *list_size);
//                 printf("Success\n");
//                 (*list_size)++;
//                 isSafe_count++;
//                 printf("Function ran %d times!\n", isSafe_count);
//             }
//         }
//     }
// }     
void appendList(board solve_list[], int *list_size, int *board_size){
    int current_level = 0;

    printf("Starting BFS for N-Queens problem.\n");
    while (current_level < *board_size) {
        printf("Exploring level: %d\n", current_level);
        int level_count = *list_size;
        int new_level_count = *list_size;

        for (int index = 0; index < level_count; index++) {
            printf("Expanding board at index %d for the next level.\n", index);
            for (int col = 0; col < *board_size; col++) {
                printf("Trying to place queen at level %d, column %d\n", current_level, col);
                if (isSafe(&solve_list[index], *board_size, current_level, col)) {
                    printf("Position is safe. Placing queen.\n");

                    board newBoard;
                    deepCopy(&solve_list[index], &newBoard, *board_size);
                    newBoard.chessboard[current_level][col] = QUEEN;

                    if (!compareBoard(&newBoard, solve_list, *list_size, *board_size)) {
                        if (new_level_count < MAX_BOARD) {
                            solve_list[new_level_count] = newBoard;
                            new_level_count++;
                            printf("New board state added at index %d\n", new_level_count - 1);
                        } else {
                            printf("MAX_BOARD limit reached. Cannot add more states.\n");
                            return;
                        }
                    } else {
                        printf("Identical board state found, not adding to list.\n");
                    }
                } else {
                    printf("Position at level %d, column %d is not safe. Trying next column.\n", current_level, col);
                }
            }
        }

        *list_size = new_level_count;
        printf("Completed level %d, total board states: %d\n", current_level, *list_size);
        current_level++;
    }
    printf("BFS complete. Total board states generated: %d\n", *list_size);
}


void QNNSolved(board solve_list[], int *list_size, int *board_size){
    appendList(solve_list, list_size, board_size);
}

void nqueenSolved(board solve_list[], int *list_size, int *board_size){
    int f = 0;

    printf("Starting to solve N-Queens problem.\n");
    while (f < *list_size) {
        for (int x = 0; x < *board_size; x++) {
            for (int y = 0; y < *board_size; y++) {
                if (isSafe(&solve_list[f], *board_size, x, y)) {
                    board tempBoard;
                    deepCopy(&solve_list[f], &tempBoard, *board_size);
                    tempBoard.chessboard[x][y] = QUEEN;

                    if (!compareBoard(&tempBoard, solve_list, *list_size, *board_size)) {
                        if (*list_size < MAX_PERM) {
                            solve_list[*list_size] = tempBoard;
                            (*list_size)++;
                        } else {
                            printf("MAX_BOARD limit reached. Cannot add more states.\n");
                            return;
                        }
                    }

                    if (countQueens(&tempBoard, *board_size) == *board_size) {
                        printf("Solution found:\n");
                        printBoard(&tempBoard, *board_size);
                    }
                }
            }
        }
        f++;
    }
}

int countQueens(board *b, int board_size){
    int queen_count = 0;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (b->chessboard[i][j] == QUEEN) {
                queen_count++;
            }
        }
    }
    return queen_count;
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
                printf("%d", j + 1); // Column numbers start from 1
                break; // Move to the next row after finding the queen - remove
            }
        }
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
    // board solve_list[MAX_PERM];
    board testParentBoard;

    //Test for empty board: making sure all characters are 'X', (2)test for checking only 1 string char in each cell    
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            testParentBoard.chessboard[row][col] = 'A';
        }
    }
    emptyBoard(&testParentBoard, n);
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            assert(testParentBoard.chessboard[row][col] = EMPTY);
            assert(strlen(&testParentBoard.chessboard[row][col]) == 1);
        }
    }

    //Test for deepCopy function: making sure for all cells A -> X
    board testChildBoard;

    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            testChildBoard.chessboard[row][col] = 'A';
        }
    }

    deepCopy(&testParentBoard, &testChildBoard, n);
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            assert(testChildBoard.chessboard[row][col] = EMPTY);
            assert(strlen(&testChildBoard.chessboard[row][col]) == 1);
        }
    }

    //Tests for Q-rules:

}
