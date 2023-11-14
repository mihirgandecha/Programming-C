#include <stdio.h>
#include <stdlib.h>

struct queen_array {
    char queen[4];
    int q_index[4];
};

int main(void) {
    struct queen_array four;
    int n = 4;

    // Initialize the arrays
    for (int i = 0; i < n; i++) {
        four.queen[i] = 'Q';      // Assign 'Q' to each queen
        four.q_index[i] = i + 1;  // Assign index (1-based)
    }

    // Print the arrays
    printf("Queens: ");
    for (int i = 0; i < n; i++) {
        printf("%c ", four.queen[i]);
    }
    printf("\nIndexes: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", four.q_index[i]);
    }
    printf("\n");

    return 0;
}
