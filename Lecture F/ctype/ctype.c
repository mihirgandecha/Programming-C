#include <stdio.h>
#include <ctype.h> // Include type managing functions

int main(void)
{
    int c;
    while ((c = getchar()) != EOF) // Continue until CNTR D is input
    {
        if (islower(c)) // Check if character is lowercase
        {
            putchar(toupper(c)); // Convert to uppercase and output
        }
        else
        {
            putchar(c); // Output non-lowercase characters as they are
        }
    }
    putchar('\n'); // Output a new line at the end
    return 0;
}
