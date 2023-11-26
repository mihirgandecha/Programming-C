#include <stdio.h>
#include <stdlib.h>

int main() {
    // Demonstrating malloc
    int *arr1 = (int *)malloc(5 * sizeof(int));
    if (arr1 == NULL) {
        perror("malloc");
        return 1;
    }

    // Initialize the allocated memory
    for (int i = 0; i < 5; i++) {
        arr1[i] = i;
    }

    // Demonstrating calloc
    int *arr2 = (int *)calloc(5, sizeof(int));
    if (arr2 == NULL) {
        perror("calloc");
        return 1;
    }

    // Demonstrating realloc
    int *arr3 = (int *)realloc(arr1, 10 * sizeof(int));
    if (arr3 == NULL) {
        perror("realloc");
        free(arr1);
        return 1;
    }

    // Initialize the new memory allocated by realloc
    for (int i = 5; i < 10; i++) {
        arr3[i] = i;
    }

    // Demonstrating memory leak
    // Uncomment the next line to intentionally create a memory leak
    // int *leaked_memory = (int *)malloc(5 * sizeof(int));

    // Freeing memory
    free(arr2);  // Free memory allocated by calloc
    arr2 = NULL; // Prevent using a dangling pointer

    free(arr3);  // Free memory allocated by realloc
    arr3 = NULL; // Prevent using a dangling pointer

    // Detecting memory leaks using GDB
    // Uncomment the next line to see the memory allocation with leaks
    // int *leaked_memory = (int *)malloc(5 * sizeof(int));

    // The program ends here

    return 0;
}
