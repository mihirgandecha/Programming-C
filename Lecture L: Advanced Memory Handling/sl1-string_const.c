//String Constants
//Failed attempt to convert all 'n' to 'N'

//Take home: We need to change flags and use:
//clangnify1.c-g3-fsanitize=undefined-fsanitize=address-onify1
//To see what is going wrong! clang does not work!!!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void nify(char s[]);

int main(void)
{
    //We created a constant and we are attempting to change it
    nify("neill"); //this is a constant
    return 0;

}

// In-Place : Swaps all ’n’-> ’N’
void nify(char s[])
{
    for(int i=0; s[i]; i++){
        if(s[i] == 'n'){
            s[i] = 'N';
        }
    }
}
//Creates a segmentation fault!
//All flags compile!
//Use sanitiser - does things like bounds checking, and which line crash
//clangnify1.c-g3-fsanitize=undefined-fsanitize=address-onify1

//How can we tell from flag specific problem?