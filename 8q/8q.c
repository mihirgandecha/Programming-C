#include "8q.h"

int main(int argc, char *argv[]){
    //Move to solveBoard after
    int n = MAX_BOARD;
    board parent_board;
    queen_array four;
    bool verbose = false;
    
    //Start of taking cmnd line arguement
    if (argc != 2){
        fprintf(stderr, "Usage: %s <fileout>\n", argv[0]);
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
    //end of cmnd line arguement

    //Initialise empty board
    emptyBoard(&parent_board, n);
    //Check in-bound
    in_bound(&parent_board, n);

    //Initalise queen array structure for board
    q_arr(&four, n);
    // Print the Q-Current Pos - convert into a function and remove at end
    printf("\nCurrent Q-Positions: \n");
    
    
    for (int i = 0; i < n; i++) {
        printf("%c at index %d is positioned at (%d, %d)\n", four.queen[i], four.q_index[i], four.row[i], four.col[i]);
    }


    printf("\n");
    //print empty board
    // printBoard(&parent_board, n);
    // printf("\n");

    //Now we have empty board of nxn, and corresponding structure of q-arr if 4 queens all indexed

    //Initialise the array list of structures for 4(N) board to solve
    board solve_list[MAX_BOARD];
    //Set f = 0 to parentBoard and print
    int f = 0;
    solve_list[f] = parent_board; 
    //print f = 0 to test array list of structure - for f=0:
    printBoard(&solve_list[f], n);
    int b = 1; //end of code
    //function for as f increments, b also increments, so that we know end of array (i.e. in 3x3 board, and we are placing 3 queens, we should have an arr of structures of N+1 possibilities so far if we place Q1 in all possible places. i.e. f = 9, b = 10) 

    //solve for f = 1 (placing 1 queen)
    f++;
    //now solve_list[1] - equate to child_board?
    board childBoard1;
    solve_list[f] = childBoard1;
    deepCopy(&parent_board, n, &solve_list[f]);
    printf("\n");
    printBoard(&childBoard1, n);
    
    // char qu[1] = 'q';
    // strcmp(solve_list[f].chessboard, qu); 
    // strcmp(childBoard1.chessboard[0][0], QUEEN);
    //print copied board
    // printf("\n");
    // printBoard(&solve_list[f], n);
    // printBoard(&childBoard1, n);
    //q_arr(&four, n);
    //printQ(&four, n);

    test();
    return 0;

    return 0;
}

    
void q_arr(queen_array *t, int board_size){
    
    t->board_size = board_size;
    
    for (int i = 0; i < board_size; i++) {
        t->queen[i] = QUEEN;      
        t->q_index[i] = i + 1;  
        t->row[i] = OUT_BOUNDS;
        t->col[i] = OUT_BOUNDS;
    }
}

bool in_bound(board *b, int board_size){
    int row, col = board_size -1;
    if (row < 0 || col < 0){
        return false;
    }
    if(row > board_size || col > board_size){
        return false;
    }
    return true;
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

void deepCopy(board *p, int board_size, board *c){
    for (int i = 0; i < board_size; i++){
        for (int j = 0; j < board_size; j++){
            c->chessboard[i][j] = p->chessboard[i][j];
        }
    }
}

void printQ(queen_array *q, int board_size){
    printf("\nCurrent Q-Positions: \n");
        for (int i = 0; i < board_size; i++) {
            printf("%c at index %d is positioned at (%d, %d)\n", q->queen[i], q->q_index[i], q->row[i], q->col[i]);
        }
}

// char isSafecr(board childBoard, *parentBoard, int n, int queen_count){

//     //For a 4x4 board: 
//     assert(isSafecr(childBoard1, *parentBoard, int 4, int 4) == 2031, count_child == 1);
//     assert(childBoard1.quenn_count == 4);
//     assert(childBoard1.empty_count == 12);
//     //Squares to be filled = n*n, make sure empty+queen = n*n
//     assert(childBoard1.queen_count + childBoard1.empty_count = n*n);



//     int f[0] = *parentBoard;
//     //Make into assert test?
//     *parentBoard.nposib = n*n;
//     *parentBoard.quenn_count = n;
//     *parentBoard.empty_count = *parentBoard.nposib - *parentBoard.queen_count;
// }
void test(void){
    queen_array six;
    q_arr(&six, 6);
    
    assert(six.board_size == 6);
    assert(six.q_index[0] == 1 && six.q_index[5] == 6);
    
}

//Assert testing - works sometimes but not always (writing first)
//Going from me writing 4x4 -> for any N up to 10
//Test for print? I just did out of bound function
//#define - should I do for Q[0] when 0 is hash defined to be INITIAL
//Comments - right now writing comments as a guide to myself, however how can I follow house style as 'effective' as i am writing?
