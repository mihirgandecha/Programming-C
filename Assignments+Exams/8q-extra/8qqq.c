#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOARDS 1000000
#define MAX_DIMENSION 10

struct board {
    int size;
    int queens[MAX_DIMENSION];
};

struct board boards[MAX_BOARDS];
int num_boards = 0;

void add_board(struct board b) {
    if (num_boards >= MAX_BOARDS) {
        printf("Error: Maximum number of boards exceeded.\n");
        exit(EXIT_FAILURE);
    }
    boards[num_boards++] = b;
}

int is_valid(struct board b, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (b.queens[i] == col || abs(b.queens[i] - col) == abs(i - row)) {
            return 0;
        }
    }
    return 1;
}

void generate_boards() {
    int f = 0;
    while (f < num_boards) {
        struct board b = boards[f++];
        if (b.size == b.queens[b.size - 1]) {
            for (int i = 0; i < b.size; i++) {
                printf("%d ", b.queens[i] + 1);
            }
            printf("\n");
        }
        for (int col = 0; col < b.size; col++) {
            if (is_valid(b, b.size, col)) {
                struct board child = b;
                child.queens[child.size++] = col;
                int is_duplicate = 0;
                for (int i = 0; i < num_boards; i++) {
                    if (child.size == boards[i].size && memcmp(child.queens, boards[i].queens, child.size * sizeof(int)) == 0) {
                        is_duplicate = 1;
                        break;
                    }
                }
                if (!is_duplicate) {
                    add_board(child);
                }
            }
        }
    }
    printf("Total number of solutions: %d\n", num_boards);
}

void test() {
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <board size>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int size = atoi(argv[1]);
    if (size < 1 || size > MAX_DIMENSION) {
        printf("Error: Invalid board size.\n");
        exit(EXIT_FAILURE);
    }
    struct board b = {size, {0}};
    add_board(b);
    generate_boards();
    return 0;
}
