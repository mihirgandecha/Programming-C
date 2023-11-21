#include <stdio.h>
#include <string.h>
#include "toprow.h"

// Function to check if a string can be typed using only the letters that appear on the top row of characters on a ‘QWERTY’ keyboard.
int toprow(const char *str) {
    const char *top_row = "qwertyuiopQWERTYUIOP";

    // Loop through each character in the string.
    for (size_t i = 0; i < strlen(str); i++){
        // If the character is not found in the top row string, return 0.
        if (strchr(top_row, str[i]) == NULL) {
            return 0;
        }
    }

    // If all characters are found in the top row string, return 1.
    return 1;
}