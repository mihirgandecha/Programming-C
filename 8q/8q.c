#include "8q.h"

int main(int argc, char *argv[]){
    int n = MAX_BOARD;
    bool verbose = false;
    //User input via command line:    
    if (argc < 2 || argc > 3){
        fprintf(stderr, "Usage: %s <fileout>\n", argv[0]);
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-verbose") == 0) {
            verbose = true;
        } else {
            if (sscanf(argv[i], "%d", &n) != 1 || n <= 0 || n > MAX_BOARD) {
                fprintf(stderr, "Invalid board size. Must be a number between 1 and %d\n", MAX_BOARD);
                return EXIT_FAILURE;
            }
        }
    }
    solveNQueens(n, verbose);
    return EXIT_SUCCESS;
}

void emptyBoard(board *b, int board_size){
    for (int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            b->chessboard[i][j] = EMPTY;
        }
    }
}

void deepCopy(board *original, board *copy, int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            copy->chessboard[i][j] = original->chessboard[i][j];
        }
    }
}

int in_bound(int row, int col, int board_size){
    if (row >= 0 && row < board_size && col >= 0 && col < board_size){
        return IN_BOUND;
    }
    return OUT_BOUNDS;
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

bool Q_DiagSafe(board *b, int row, int col, int board_size){
    for (int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            if (b->chessboard[i][j] == QUEEN){
                //using (x1−x2) = (y1−y2) for diaganol check
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

bool isSafe(board *temp, int board_size, int row, int col){
    if(in_bound(row, col, board_size) == OUT_BOUNDS){
        return false;
    }
    if ((isSafe_RC(temp, board_size, row, col) && Q_DiagSafe(temp, row, col, board_size)) == false){
        return false;
    }
    return true;
}

int getMaxPerm(int board_size){
    switch(board_size) {
        case 8:
            return 800000;
        case 9:
            return 500000;
        case 10:
            return MAX_PERM;
        default:
            return 50000; // default value
    }
}

void nqueenSolved(board solve_list[], int *list_size, int *board_size){
    int max_perm = getMaxPerm(*board_size);
    for (int f = 0; f < *list_size; f++){
        for (int x = 0; x < *board_size; x++){
            for (int y = 0; y < *board_size; y++){
                if (isSafe(&solve_list[f], *board_size, x, y)){
                    board tempBoard;
                    deepCopy(&solve_list[f], &tempBoard, *board_size);
                    tempBoard.chessboard[x][y] = QUEEN;
                    if (!compareBoard(&tempBoard, solve_list, *list_size, *board_size) && *list_size < max_perm){
                        solve_list[*list_size] = tempBoard;
                        (*list_size)++;
                    }
                }
            }
        }
    }
}

int countQueens(board *b, int board_size){
    int queen_count = 0;
    for (int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            if (b->chessboard[i][j] == QUEEN){
                queen_count++;
            }
        }
    }
    return queen_count;
}

bool areBoardsIdentical(board *board1, board *board2, int board_size){
    for (int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            if (board1->chessboard[i][j] != board2->chessboard[i][j]){
                return false;
            }
        }
    }
    return true;
}

bool compareBoard(board *current_board, board solve_list[], int num_boards, int board_size){
    for (int b = 0; b < num_boards; b++){
        if (areBoardsIdentical(current_board, &solve_list[b], board_size)){
            return true;
        }
    }
    return false;
}

void printBoardSolution(board *b, int board_size){
    for (int i = 0; i < board_size; i++) {
        bool found = false;
        for (int j = 0; j < board_size && !found; j++) {
            if (b->chessboard[i][j] == QUEEN) {
                printf("%d", j + 1); //column numbers start from 1
                found = true;
            }
        }
    }
    printf("\n");
}

void solveNQueens(int n, int verbose){
    board parentBoard;
    board solve_list[MAX_PERM];
    emptyBoard(&parentBoard, n);

    int f = 0;
    solve_list[f] = parentBoard;
    int list_size = 1;
    //Solve NQueen using Breadth-First Search Algorithm
    nqueenSolved(solve_list, &list_size, &n);
    int solution_count = 0;
    for (int i = 0; i < list_size; i++) {
        if (countQueens(&solve_list[i], n) == n){
            solution_count++;        
            if (verbose){
                printBoardSolution(&solve_list[i], n);
            }
        }
    }
    printf("%d solutions\n", solution_count);
}

//Testing Functions:
void testEmptyBoard(int n){
    board testParentBoard;
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            testParentBoard.chessboard[row][col] = 'A';
        }
    }
    emptyBoard(&testParentBoard, n);
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            assert(testParentBoard.chessboard[row][col] == EMPTY);
            assert(strlen(&testParentBoard.chessboard[row][col]) == 1);
        }
    }
}

void testDeepCopy(int n){
    board testParentBoard;
    board testChildBoard;

    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            testChildBoard.chessboard[row][col] = 'A';
        }
    }
    deepCopy(&testParentBoard, &testChildBoard, n);
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            assert(testChildBoard.chessboard[row][col] == EMPTY);
            assert(strlen(&testChildBoard.chessboard[row][col]) == 1);
        }
    }
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

void test_QDiagSafe(void){
    int board_size = MAX_BOARD;
    board testBoard;
    emptyBoard(&testBoard, board_size);
    testBoard.chessboard[0][0] = QUEEN;
    
    assert(Q_DiagSafe(&testBoard, 9, 9, board_size) == false);
    testBoard.chessboard[0][9] = QUEEN;
    assert(Q_DiagSafe(&testBoard, 9, 0, board_size) == false);
    testBoard.chessboard[9][0] = QUEEN;
    assert(Q_DiagSafe(&testBoard, 0, 9, board_size) == false);
    testBoard.chessboard[9][9] = QUEEN;
    assert(Q_DiagSafe(&testBoard, 0, 0, board_size) == false);
    
    board testBoard2;
    int board_size2 = 5;
    emptyBoard(&testBoard2, board_size2);
    testBoard.chessboard[2][2] = QUEEN; 
    assert(Q_DiagSafe(&testBoard, 4, 3, board_size2) == true); 
    assert(Q_DiagSafe(&testBoard, 1, 1, board_size2) == false);
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
    assert(isSafe(&testBoard, board_size, 0, 1) == true); 
    assert(isSafe(&testBoard, board_size, 2, 0) == true);
    assert(isSafe(&testBoard, board_size, 1, 1) == false);
    assert(isSafe(&testBoard, board_size, -1, 0) == false);
}

void test(void){
    int n = 3;
    testEmptyBoard(n);
    testDeepCopy(n);

    //Queen Placement Testing:
    testin_bound();
    test_isSafeRC();
    test_QDiagSafe();
    test_isSafe();
}
