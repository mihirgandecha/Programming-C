// Function to count the number of mines around a given cell
int count_mines_around(board b, int x, int y);

// Function to count the number of unknowns around a given cell
int count_unknowns_around(board b, int x, int y);

// Functions to apply the solving rules
bool apply_rule_one(board* b);
bool apply_rule_two(board* b);

// Main function to solve the board
board solve_board(board b);

int count_mines_around(board b, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int new_x = x + i;
            int new_y = y + j;
            if (new_x >= 0 && new_x < b.h && new_y >= 0 && new_y < b.w) {
                if (b.grid[new_x][new_y] == MINE) {
                    count++;
                }
            }
        }
    }
    return count;
}

int count_unknowns_around(board b, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int new_x = x + i;
            int new_y = y + j;
            if (new_x >= 0 && new_x < b.h && new_y >= 0 && new_y < b.w) {
                if (b.grid[new_x][new_y] == UNK) {
                    count++;
                }
            }
        }
    }
    return count;
}

bool apply_rule_one(board* b) {
    bool changed = false;
    for (int i = 0; i < b->h; i++) {
        for (int j = 0; j < b->w; j++) {
            if (b->grid[i][j] == UNK) {
                int mine_count = count_mines_around(*b, i, j);
                if (mine_count == b->totmines) {
                    b->grid[i][j] = '0' + mine_count; // Convert integer to char
                    changed = true;
                }
            }
        }
    }
    return changed;
}

bool apply_rule_two(board* b) {
    bool changed = false;
    for (int i = 0; i < b->h; i++) {
        for (int j = 0; j < b->w; j++) {
            if (isdigit(b->grid[i][j])) { // Check if the cell is a numbered one
                int mine_count = count_mines_around(*b, i, j);
                int unknown_count = count_unknowns_around(*b, i, j);
                int number_in_cell = b->grid[i][j] - '0'; // Convert char to integer

                if (number_in_cell - mine_count == unknown_count) {
                    // Mark all unknowns around as mines
                    for (int x = -1; x <= 1; x++) {
                        for (int y = -1; y <= 1; y++) {
                            int new_x = i + x;
                            int new_y = j + y;
                            if (new_x >= 0 && new_x < b->h && new_y >= 0 && new_y < b->w) {
                                if (b->grid[new_x][new_y] == UNK) {
                                    b->grid[new_x][new_y] = MINE;
                                    changed = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return changed;
}

board solve_board(board b) {
    bool changed;
    do {
        changed = apply_rule_one(&b);
        changed |= apply_rule_two(&b); // |= is used to ensure both functions are always called
    } while (changed); // Repeat if any changes were made in the last pass

    return b;
}
