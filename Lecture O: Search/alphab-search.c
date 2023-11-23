#include <stdio.h>
#include <string.h>
#include <assert.h>

#define NOTFOUND -1
#define NUMPEOPLE 6

typedef struct person {
    char* name;
    int age;
} person;

int findAge(const char* name, const person* p, int n);

int main(void) {
    person ppl[NUMPEOPLE] = {
        {"Ackerby", 21},
        {"Bloggs", 25},
        {"Delta", 26},
        {"Dalton", 25},
        {"Eggson", 22},
        {"Fulton", 41}
    };

    assert(findAge("Eggson", ppl, NUMPEOPLE) == 22);
    assert(findAge("Campbell", ppl, NUMPEOPLE) == NOTFOUND);

    return 0;
}

int findAge(const char* name, const person* p, int n) {
    for (int j = 0; j < n; j++){
        int m = strcmp(name, p[j].name);
        if (m == 0){
            return p[j].age;
        }
        /*if it returns a negative value, assuming the array is in alphabetical order, 
        a negative return indicates str2 (p[j].name) ascii is 
        greater than str1 (name - assertion)*/
        //checking second char of chumley, a-h=-7. Therefore logic works for when same first char too!
        //changed to Delta = -1, returned!
        if (m < 0){
            return NOTFOUND;
        }
    }
    return NOTFOUND;
}
