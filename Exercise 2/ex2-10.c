//Secret Code Exercise
#include <stdio.h>
/*#include <assert.h>*/

#define CHANGE ('z' - 'a')
/*
int scode(int a);
void test(void);*/

int main(void){

    /*test();*/
    char a = 'a';
    char b = 'z';
    printf("%i\n", a);
    printf("%i\n", b);
    printf("%i\n", CHANGE);


    return 0;
}
/*
int scode(int b){ 

    printf("Please type in character(s), which will convert into secret code.\n \
    Note that only characters from a to z will be affected, and non-characters will\n \")
    not convert. \n\t\t Important! \n To terminate the code please use character '!'\n \
    - otherwise the program will enter an infinite loop. \n\n AKA NOT GOOD!");

    int b;
    while ((b = getchar() ! '!')){


    }


    return b;
}


void test(void){ //4 tests + add your own!

assert(scode('a') == 'z');
assert(scode('b') == 'y');
assert(scode('c') == 'x'); //Q Is there a quick way of checking for all characters?
assert(scode('The Quick Brown Fox Jumps Over the Lazy Dog !')\
 == 'Gsv Jfrxp Yildm Ulc Qfnkh Levi gsv Ozab Wlt !');

//Tests for non-character are returned unaffected:
assert(scode('!') != ) //Find out the conversion by printing.
//(1) Do one more test for one non-character
//(2) Test for Space bar? _
} */
