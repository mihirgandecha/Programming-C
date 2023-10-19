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




// Count the mines around the cell at position (x, y).
int countMinesAroundCell(board b, int x, int y) {
    int mines = 0;
    // Check the surrounding cells.
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx, ny = y + dy;
            // Check if it's within the board and if there's a mine.
            if (nx >= 0 && nx < b.h && ny >= 0 && ny < b.w && b.grid[nx][ny] == MINE) {
                mines++;
            }
        }
    }
    return mines;
}

// Count the unknowns around the cell at position (x, y).
int countUnknownsAroundCell(board b, int x, int y) {
    int unknowns = 0;
    // Check the surrounding cells.
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = x + dx, ny = y + dy;
            // Check if it's within the board and if it's an unknown cell.
            if (nx >= 0 && nx < b.h && ny >= 0 && ny < b.w && b.grid[nx][ny] == UNK) {
                unknowns++;
            }
        }
    }
    return unknowns;
}

// Apply the first solving rule: if the number of mines equals 'totmines', mark the cell.
board applyRuleOne(board b) {
    // Go through each cell.
    for (int i = 0; i < b.h; i++) {
        for (int j = 0; j < b.w; j++) {
            if (b.grid[i][j] == UNK) {
                int mines = countMinesAroundCell(b, i, j);
                if (mines == b.totmines) {
                    b.grid[i][j] = '0' + mines; // Update the cell with the number of surrounding mines.
                }
            }
        }
    }
    return b; // Return the updated board.
}

// Apply the second solving rule: if the number of unknowns equals the total minus surrounding mines, they're all mines.
board applyRuleTwo(board b) {
    // Go through each cell.
    for (int i = 0; i < b.h; i++) {
        for (int j = 0; j < b.w; j++) {
            // Only proceed if the cell is a number.
            if (isdigit(b.grid[i][j])) {
                int mines = countMinesAroundCell(b, i, j);
                int unknowns = countUnknownsAroundCell(b, i, j);
                int total = b.grid[i][j] - '0';

                // If the number of unknowns equals the 'total' minus counted mines, all unknowns are mines.
                if (total - mines == unknowns) {
                    // Update the unknown cells to mines.
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            int nx = i + dx, ny = j + dy;
                            if (nx >= 0 && nx < b.h && ny >= 0 && ny < b.w && b.grid[nx][ny] == UNK) {
                                b.grid[nx][ny] = MINE;
                            }
                        }
                    }
                }
            }
        }
    }
    return b; // Return the updated board.
}

// Main function to apply the rules iteratively until the board is solved.
board solveBoard(board b) {
    bool hasChanged;
    do {
        board prevBoard = b; // Keep track of the state before the rules are applied.

        b = applyRuleOne(b);
        b = applyRuleTwo(b);

        hasChanged = !(memcmp(prevBoard.grid, b.grid, sizeof(b.grid)) == 0); // Check if the board has changed.
    } while (hasChanged); // Repeat if there was any change.

    return b; // Return the solved board.
}
