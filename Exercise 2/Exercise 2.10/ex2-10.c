//Secret Code Exercise
#include <stdio.h>
#include <assert.h>

#define LOWERCASE_CHANGE(c) ('a' + ('z' - (c))) 
#define UPPERCASE_CHANGE(c) ('A' + ('Z' - (c)))

int scode(int b);
void test(void);

int main(void){

    printf(" Please type in character(s), which will convert into secret code.\n \
Note that only characters from a to z will be affected, and non-characters will\n \
not convert. \n\t\t\t Important! \n To terminate the code please use character '!' \
- otherwise the program will enter an infinite loop. \n\n AKA NOT GOOD!\nPlease input your character(s): ");

    int c;
    while ((c = getchar()) != '!'){
        putchar(scode(c));
    }
    putchar('\n');
    test();
    return 0;
}

int scode(int b){ 

    if(b >= 'a' && b <= 'z'){
        return LOWERCASE_CHANGE(b); 
    }
    else if (b >= 'A' && b <= 'Z'){
        return UPPERCASE_CHANGE(b);
    }
    else{
        return (b);
    }

}

void test(void){ 

assert(scode('a') == 'z');
assert(scode('b') == 'y');
assert(scode('c') == 'x'); 
assert(scode('z') == 'a');
assert(scode('y') == 'b');
assert(scode('x') == 'c');

//Test for non-character are returned unaffected:
assert(scode('?') =='?'); 
} 
