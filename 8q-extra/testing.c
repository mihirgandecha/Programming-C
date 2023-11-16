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

void printQ(queen_array *q, int board_size){
    printf("\nCurrent Q-Positions: \n");
        for (int i = 0; i < board_size; i++) {
            printf("%c at index %d is positioned at (%d, %d)\n", q->queen[i], q->q_index[i], q->row[i], q->col[i]);
        }
}
