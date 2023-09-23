#include <stdio.h>

int main(void) {
    int choice;

    printf("Enter a choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Option 1 selected.\n");
        // Return 1 to indicate a specific outcome or condition
        return 1;
    } else if (choice == 2) {
        printf("Option 2 selected.\n");
        // Return 2 to indicate another specific outcome or condition
        return 2;
    } else {
        printf("Invalid choice.\n");
        // Return a non-zero value (e.g., 3) to indicate an error or invalid input
        return 3;
    }
}
