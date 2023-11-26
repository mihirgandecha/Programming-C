#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_BOARD 10
#define QUEEN 'Q'
#define EMPTY 'X'
#define INDEX_POSITION 1000

//Write a solution for NQueen problem for 4x4
typedef struct queen_array {
    int n;
    char queen[MAX_BOARD];
    int q_index[MAX_BOARD];
} queen_array;

typedef struct board {
   char chessboard[MAX_BOARD][MAX_BOARD];
} board;

void q_arr(queen_array *t, int board_size);
void emptyBoard(board *b, int board_size);
void printBoard(board *b, int board_size);

bool RowSafe(chess_array *board, int board_size);
bool ColSafe(chess_array *board, int board_size);
void test(void);

int main(void) {

    int cmndIn = 10; //this needs to come from command line, making sure not more than 10

    // Print the arrays - remove
    printf("n is: %i\n", four.n);
    printf("Queens: ");
    for (int i = 0; i < cmndIn; i++) {
        printf("%c ", four.queen[i]);
    }
    printf("\nIndexes: ");
    for (int i = 0; i < cmndIn; i++) {
        printf("%d ", four.q_index[i]);
    }
    printf("\n");
    test();
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

void q_arr(queen_array *t, int board_size){
    
    t->n = board_size;
    
    for (int i = 0; i < board_size; i++) {
        t->queen[i] = QUEEN;      
        t->q_index[i] = i + 1;  
    }
}

void solveboard(){
    board chess_array [MAX_BOARD]; 
    int board_size = 4;
    int f = 0;
    board four;

    chess_array[f] = emptyBoard(&four, board_size);
    f++;

    //now f = 1
    chess_array[f] = emptyBoard(&four, board_size);
    char q_one = QUEEN;
    board->chessboard[0][0] = q_one;
    f++;

    //now f = 2, place next queen
    chess_array[f] = emptyBoard(&four, board_size);
    char q_two = QUEEN;

    if(RowSafe())



    //Check for safe place
    assert(board->chessboard[int row][int column] for q2 is safe);
    assert(bool q2 isRowSafe(board four_q2, int row, int column, char q1, char q2) == SAFE);
    
    bool q2 = RowSafe(chess_array *board, int board_size);
    assert(q2 == bool false);

    bool q2 = ColSafe(chess_array *board, int board_size);
    assert(q2 == bool false);




    
}

bool RowSafe(board *check, int board_size){
    int queen_count = 0;
    int row = 0; //change
    for (int col = 0; col < board_size; col++){
        if (board->chessboard[row][col] == 'Q'){
            queen_count++;
            if(queen_count > 1){
                return false;
            }

        }
    }
    return true;
}


bool ColSafe(chess_array *board, int board_size){
    int queen_count = 0;
    int col = 0; //change
    for (int row = 0; row < board_size; row++){
        if (board->chessboard[row][col] == 'Q'){
            queen_count++;
            if(queen_count > 1){
                return false;
            }

        }
    }
    return true;
}

bool in_bound(board* b, int row, int col, int board_size){
    if (row < 0 || col < 0){
        return false;
    }
    if(row > board_size || col > board_size){
        return false;
    }
    return true;
}

bool DiagSafe(chess_array *board, int board_size){
    

    //In a 3x3 board
    board three;
    if (three->chessboard[1][1] = 'Q';){
        //top left diaganol
        assert(three->chessboard[0][0] = 'Q');
        //top right diaganol
        assert(three->chessboard[0][2] = 'Q');
        //bottom left diaganol
        assert(three->chessboard[2][0] = 'Q');
        //bottom right diaganol
        assert(three->chessboard[2][2] = 'Q');
    }
    //top left diaganol
    bool three_inbound = in_bound(&three, 3, 3, 3);

    for (int row, int col; three_inbound == true; row--, col--){
        if (three[row][col] == 'Q'){
            return false;
        }
    }
    
    //top right diaganol
    for (int row, int col; three_inbound == true; row++, col--){
        if (three[row][col] == 'Q'){
            return false;
        }
    }
    
    //bottom left diaganol
    for (int row, int col; three_inbound == true; row--, col++){
        if (three[row][col] == 'Q'){
            return false;
        }
    }

    //bottom right diaganol
    for (int row, int col; three_inbound == true; row++, col++){
        if (three[row][col] == 'Q'){
            return false;
        }
    }
    return true;

}

bool DiagSafe(chess_array *board, int board_size){
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (board->chessboard[i][j] == QUEEN) {
                for (int k = 1; k < board_size; k++) {
                    if ((i - k >= 0 && board->chessboard[i - k][j - k] == QUEEN) ||
                        (i - k >= 0 && board->chessboard[i - k][j + k] == QUEEN) ||
                        (i + k < board_size && board->chessboard[i + k][j - k] == QUEEN) ||
                        (i + k < board_size && board->chessboard[i + k][j + k] == QUEEN)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void test(void){
    queen_array six;
    q_arr(&six, 6);
    
    assert(six.n == 6);
    assert(six.q_index[0] == 1 && six.q_index[5] == 6);
    //     //test for magic numbers to do!
//     queen_array six;
//     q_arr(&six, 6);
    
//     assert(six.board_size == 6);
//     assert(six.q_index[0] == 1 && six.q_index[5] == 6);
    
//     //In a 3x3 board
//     board three;
//     if (three->chessboard[1][1] = 'Q';){
//         //top left diaganol
//         assert(three->chessboard[0][0] = 'Q');
//         //top right diaganol
//         assert(three->chessboard[0][2] = 'Q');
//         //bottom left diaganol
//         assert(three->chessboard[2][0] = 'Q');
//         //bottom right diaganol
//         assert(three->chessboard[2][2] = 'Q');
//     }
}

typedef struct queen_array {
    int board_size;
    char queen[MAX_BOARD];
    int q_index[MAX_BOARD];
    int row[MAX_BOARD];
    int col[MAX_BOARD];
} queen_array;

void q_arr(queen_array *t, int board_size){
    
    t->board_size = board_size;
    
    for (int i = 0; i < board_size; i++){
        t->queen[i] = QUEEN;      
        t->q_index[i] = i + 1;  
        t->row[i] = OUT_BOUNDS;
        t->col[i] = OUT_BOUNDS;
    }
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


void printQ(queen_array *q, int board_size){
    printf("\nCurrent Q-Positions: \n");
        for (int i = 0; i < board_size; i++) {
            printf("%c at index %d is positioned at (%d, %d)\n", q->queen[i], q->q_index[i], q->row[i], q->col[i]);
        }
}

void generate_childBoard(board *parent_board, int board_size, board solve_list[], int *b)


    // //breadth-first search implementation:
    // //Initialise the array list of structures for 4(N) board to solve
    // board solve_list[MAX_PERM];
    // //f representing front of queue and b representing back of queue
    // int f = 0;
    // int b = 1; 
    
    // board parentBoard;
    // emptyBoard(&parentBoard, n);
    // solve_list[f] = parentBoard;

    // board childBoard;
    // deepCopy(&solve_list[f], &childBoard, n);
    // solve_list[b] = childBoard;

    // printBoard(&solve_list[b], n);
    // printf("\n");

    // //place q1
    // int b_q1max = n*n;
    
    // for (int i = 0; i < n; i++){
    //     solve_list[b].chessboard[i][i] = QUEEN;
    //     b++;
    //     }

    // printBoard(&solve_list[b], n);
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

    void solveBoard(board *solve_list, int *b, int board_size, bool verbose) {
    int start = 0;
    do {
        int current_end = *b;
        for (int i = start; i < current_end; i++) {
            for (int row = 0; row < board_size; row++) {
                for (int col = 0; col < board_size; col++) {
                    if (isSafe(&solve_list[i], board_size, row, col)) {
                        board childBoard;
                        deepCopy(&solve_list[i], &childBoard, board_size);
                        childBoard.chessboard[row][col] = QUEEN;
                        if (!compareBoard(&childBoard, solve_list, *b, board_size)) {
                            solve_list[*b] = childBoard;
                            (*b)++;
                            if (isCompleteSolution(&childBoard, board_size)) {
                                printSolution(&childBoard, board_size, verbose);
                            }
                        }
                    }
                }
            }
        }
        start = current_end;
    } while (start != *b);
}

void printSolution(board *b, int board_size, bool verbose) {
    if (verbose) {
        for (int i = 0; i < board_size; i++) {
            for (int j = 0; j < board_size; j++) {
                if (b->chessboard[i][j] == QUEEN) {
                    printf("%d", j + 1);  // Print column index of queen in each row
                }
            }
        }
        printf("\n");
    }
}

bool compareBoard(board *newBoard, board *solve_list, int b, int board_size) {
    for (int i = 0; i < b; i++) {
        if (compareBoard(newBoard, &solve_list[i], board_size)) {
            return true;  // Duplicate board found
        }
    }
    return false;  // No duplicates
}

bool isCompleteSolution(board *b, int board_size) {
    int queen_count = 0;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (b->chessboard[i][j] == QUEEN) {
                queen_count++;
            }
        }
    }
    return queen_count == board_size;  // Check if all queens are placed
}

// ... [rest of the functions like isSafe, deepCopy, etc.] ...

int main(int argc, char *argv[]) {
    // ... [existing setup code] ...

    int verbose_level = 0;
    if (argc == 3) {
        verbose_level = atoi(argv[2]);
    }

    board solve_list[MAX_PERM];
    int f = 0;
    int b = 0;

    placeQ1(solve_list, &b, n);
    solveBoard(solve_list, &b, n, verbose_level >= 6);

    // ... [rest of main function] ...
    return 0;
}

void generate_childBoard(board *parent_board, int board_size, board solve_list[], int *b){
    for (int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            if(isSafe(parent_board, board_size, i, j)){
                board childBoard;
                deepCopy(parent_board, &childBoard, board_size);
                childBoard.chessboard[i][j] = QUEEN;
                solve_list[*b] = childBoard;
                (*b)++;
            }
        }
    }
}

board create_emptyBoard(board *b, board arrayof_struct[]){
    for (int i = 0; i < *n; i++){
        for (int j = 0; j < *n; j++){
            b->chessboard[i][j] = EMPTY;
        }
    }
    int f = 0;
    arrayof_struct[f] = board b;
    //returns an array of structure of position f = 0, where f = 0 is filled with empty values
    return arrayof_struct[f];
}
