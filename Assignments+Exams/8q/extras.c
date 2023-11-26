
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