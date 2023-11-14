#include "ms.h"

#define NUM_VALID_CHARS 11
#define NUM_NEIGHBORS 8

// tests if rule 1 is valid
bool rule1(board* b, int j, int i);

// tests if rule 2 is valid
bool rule2(board* b, int j, int i);

// returns the total number of mines visible on the grid
int num_mines(board* b);

// returns the the number of neighbors of a specific type (MINE, UNK)
unsigned short num_neighbors(board* b, int y, int x, char type);

// fills the neighbors of `type` with `set_type`
void fill_neighbors(board* b, int y, int x, char type, char set_type);

// returns true if an x/y pair is within the grid
bool in_bounds(board* b, int j, int i);

// returns true if char c is a valid grid character
bool char_is_valid(char c);

// returns the number of mines in the given string
unsigned num_mines_in_str(char* str);


board solve_board(board b)
{
    int j, i;
    int* cell;
    bool search_exhausted = false;
    while (!search_exhausted) {
        search_exhausted = true;
        for (j=0; j<b.h; j++) {
            for (i=0; i<b.w; i++) {
                if (rule1(&b, j, i)) {
                    cell = &b.grid[j][i];
                    *cell = '0' + num_neighbors(&b, j, i, MINE);
                    search_exhausted = false;
                }
                else if (rule2(&b, j, i)) {
                    fill_neighbors(&b, j, i, UNK, MINE);
                    search_exhausted = false;
                }
            }
       }
    }
    return b;
}


bool rule1(board* b, int j, int i)
{
    int* cell = &b->grid[j][i];
    // if all mines are found and target cell is unknown
    if (num_mines(b) == b->totmines && *cell == UNK) {
        return true;
    }
    return false;
}


bool rule2(board* b, int j, int i)
{
    int* cell = &b->grid[j][i];
    // if cell is a number (not UNK or MINE)
    if (*cell != UNK && *cell != MINE) {   
        int n = *cell - '0';
        int m = num_neighbors(b, j, i, UNK);
        // are there UNK neighbors and cell num suggests they are MINEs?
        if (m > 0 && num_neighbors(b, j, i, MINE) == n-m) {
            return true;
        }
    }
    return false;
}


int num_mines(board* b)
{
    int count=0;
    for (int j=0; j<b->h; j++) {
        for (int i=0; i<b->w; i++) {
            if (b->grid[j][i] == MINE) {
                count++;
            }
        }
    }
    return count;
}


void fill_neighbors(board* b, int y, int x, char type, char set_type)
{
    int new_y, new_x;  
    int row_offsets[NUM_NEIGHBORS] = {-1, -1, -1,  0,  1,  1,  1,  0};
    int col_offsets[NUM_NEIGHBORS] = {-1,  0,  1,  1,  1,  0, -1, -1};
    
    for (int i=0; i<NUM_NEIGHBORS; i++) {
        new_y = y + row_offsets[i];
        new_x = x + col_offsets[i];
        if (in_bounds(b, new_y, new_x)) {
            if (b->grid[new_y][new_x] == type) {
                b->grid[new_y][new_x] = set_type;
            }    
        }
    }
}


unsigned short num_neighbors(board* b, int y, int x, char type)
{
    int new_y, new_x;  
    int row_offsets[NUM_NEIGHBORS] = {-1, -1, -1,  0,  1,  1,  1,  0};
    int col_offsets[NUM_NEIGHBORS] = {-1,  0,  1,  1,  1,  0, -1, -1};
    unsigned short count=0;

    for (int i=0; i<NUM_NEIGHBORS; i++) {
        new_y = y + row_offsets[i];
        new_x = x + col_offsets[i];
        if (in_bounds(b, new_y, new_x)) {
            if (b->grid[new_y][new_x] == type) {
                count++;
            }
        }
    }
    return count;
}


bool in_bounds(board* b, int j, int i)
{
    if (j < 0 || i < 0) {
        return false;
    }
    if (j < b->h && i < b->w) {
        return true;
    }
    return false;
}


void board2str(char s[MAXSQ*MAXSQ+1], board b)
{
    int str_i = 0;
    for (int j=0; j<b.h; j++) {
        for (int i=0; i<b.w; i++) {
            s[str_i] = b.grid[j][i];
            str_i++;
        }
    }
    s[str_i] = '\0';
}


bool syntax_check(unsigned totmines, unsigned width, unsigned height, char inp[MAXSQ*MAXSQ+1])
{
    unsigned len = strlen(inp);

    if (len != width*height) {
        return false;
    }
    for (int i=0; i<(int)len; i++) {
        if (!char_is_valid(inp[i])) {
            return false;
        }
    }
    if (num_mines_in_str(inp) > totmines) {
        return false;
    }
    return true;
}


bool char_is_valid(char c)
{
    char valid_chars[NUM_VALID_CHARS] = "012345678?X";
    for (int i=0; i<NUM_VALID_CHARS; i++) {
        if (valid_chars[i] == c) {
            return true;
        }
    }
    return false;
}


unsigned num_mines_in_str(char* str)
{
    unsigned count = 0;
    int len = strlen(str);
    for (int i=0; i<len; i++) {
        if (str[i] == MINE) {
            count++;
        }
    }
    return count;
}


board make_board(int minecount, int width, int height, char inp[MAXSQ*MAXSQ+1])
{
    board b;
    b.w = width;
    b.h = height;
    b.totmines = minecount;

    int str_i = 0;
    for (int j=0; j<b.h; j++) {
        for (int i=0; i<b.w; i++) {
            b.grid[j][i] = inp[str_i]; 
            str_i++;
        }
    }
    return b;
}


void test(void)
{
    board b;
    char s[MAXSQ*MAXSQ+1];

    // rectangular board
    strcpy(s, "????1???");
    b = make_board(4, 2, 4, s);
    b = solve_board(b);
    board2str(s, b);
    assert(strcmp(s, "????1???") == 0);

    strcpy(s, "XXXX?XXXX");
    assert(num_mines_in_str(s) == 8);
    b = make_board(8, 3, 3, s);
    assert(rule1(&b, 1, 1) == true);
    assert(in_bounds(&b, 2, 0) == true);
    assert(in_bounds(&b, -1, 0) == false);
    assert(in_bounds(&b, 3, 3) == false);
    
    strcpy(s, "X??X8X??X");
    b = make_board(8, 3, 3, s);
    assert(rule2(&b, 1, 1) == true);
    assert(num_neighbors(&b, 1, 1, UNK) == 4);
    assert(num_neighbors(&b, 0, 1, MINE) == 3);
    assert(num_mines(&b) == 4);
    fill_neighbors(&b, 1, 1, UNK, MINE);
    board2str(s, b);
    assert(strcmp(s, "XXXX8XXXX") == 0);

    strcpy(s, "????X????");
    fill_neighbors(&b, 1, 1, UNK, MINE);
    board2str(s, b);
    assert(strcmp(s, "XXXX8XXXX") == 0);

    assert(char_is_valid('8') == true);
    assert(char_is_valid('9') == false);
    assert(char_is_valid('\0') == false);

    assert(num_mines_in_str("") == 0);
    assert(num_mines_in_str("X????XX??X?") == 4);
    assert(num_mines_in_str("X") == 1);
    assert(num_mines_in_str("X?X") == 2);
}
//72 - ask for what feedback was
