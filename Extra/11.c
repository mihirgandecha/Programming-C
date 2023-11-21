#include "toprow.h"

int toprow(const char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!(s[i] >= 'q' && s[i] <= 'p') && !(s[i] >= 'Q' && s[i] <= 'P'))
        {
            return false;
        }
    }

    return true;
}