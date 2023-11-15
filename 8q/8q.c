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
    
    if (sscanf(argv[1], "%d", &n) != 1 || n <= 0 || n > MAX_BOARD){
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
    printQ(&four, n);

    
    //Initialise the array list of structures for 4(N) board to solve
    board solve_list[MAX_BOARD * MAX_BOARD]; //how many squares to place Q
    //Set f = 0 to indicate start of struct array
    int f = 0;
    int b = 0; //end of struct array
    //Initialise parentBoard and equate to f=0
    board parentBoard;
    emptyBoard(&parentBoard, n);
    solve_list[f] = parentBoard; 
    printBoard(&solve_list[f], n);
    
    b++;
    board childBoard;
    deepCopy(&solve_list[f], n, &childBoard);
    solve_list[b] = childBoard;
    printf("\n");
    
    //function for as f increments, b also increments, so that we know end of array (i.e. in 3x3 board, and we are placing 3 queens, we should have an arr of structures of N+1 possibilities so far if we place Q1 in all possible places. i.e. f = 9, b = 10) 
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            deepCopy(&solve_list[f], n, &solve_list[b]);
            solve_list[b].chessboard[i][j] = QUEEN;
            printBoard(&solve_list[b], n);
            printf("\n");
            b++;
        }
    }
    // solve_list[b].chessboard[i][j] = QUEEN;
    printBoard(&solve_list[b], n);
    printf("\n");
    

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

//check if a queen is safe in a column or row
bool isSafe(board *b, int board_size, int row, int col){
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


void test(void){
    queen_array six;
    q_arr(&six, 6);
    
    assert(six.board_size == 6);
    assert(six.q_index[0] == 1 && six.q_index[5] == 6);
    
}
