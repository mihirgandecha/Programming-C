#include <stdio.h>
#include <assert.h>

int mult(int a, int b);
void test(void);

int main(void)
{
    test();

    return 0;
}

int mult(int a, int b)
{
    int result = a;
    for (int i = 1; i < b; ++i){
        result += a; 
        }
    if (b == 0){
        result = 0;
    }
    return result;
    }

void test(void)
{
    assert(mult(5, 3) == 15);
    assert(mult(3, 5) == 15);
    assert(mult(0, 3) == 0);
    assert(mult(3, 0) == 0);
    assert(mult(1, 8) == 8);
    assert(mult(8, 1) == 8);
}