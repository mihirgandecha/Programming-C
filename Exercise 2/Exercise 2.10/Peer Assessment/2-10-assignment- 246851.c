//Secret Code Exercise
#include <stdio.h>
#include <assert.h>

#define CHANGE 'a' + 'z' 

int scode(int b);
void test(void);

int main(void){

    printf(" Please type in character(s), which will convert into secret code.\n \
Note that only characters from a to z will be affected, and non-characters will\n \
not convert. \n\t\t\t Important! \n To terminate the code please use character '!' \
- otherwise the program will enter an infinite loop. \n\n AKA NOT GOOD!\nPlease input your character(s): ");

    
    test();
    return 0;
}

int scode(int b){ 

    while ((b = getchar()) != '!'){
        if(b >= 'a' && b <= 'z'){
            putchar(b + CHANGE); 
        }
        else{
            putchar(b);
        }

    putchar('\n');
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
