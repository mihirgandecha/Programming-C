// iterating through each character in the string
while (s[i] != '\0')
{
    // checking if the character is an alphabet
    if (isalpha(s[i]))
    {
        // checking if the character is a lowercase letter not in the top row characters
        if (islower(s[i]) && strchr("qwertyuiop", s[i]) == NULL)
        {
            flag = false;
            break;
        }

        // checking if the character is an uppercase letter not in the top row characters
        if (isupper(s[i]) && strchr("QWERTYUIOP", s[i]) == NULL)
        {
            flag = false;
            break;
        }
    }
    i++;
}

return flag;