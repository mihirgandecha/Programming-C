#include <stdio.h>
#include <assert.h>

int mult(int a, int b);
void test(void);

int main(void)
{
    int count = mult(3,5);
    //test();
    printf("%d\n", count);
    return 0;
}

int mult(int a, int b)
{
    int count = 0;
    for (int i = 0; i < b; ++i) {
        count += a;
    }
    return count;
}

void test(void)
{
    assert(mult(5, 3) == 15);
    assert(mult(3, 5) == 15);
    assert(mult(0, 3) == 0);
    assert(mult(3, 0) == 0);
    assert(mult(1, 8) == 8);
    assert(mult(8, 1) == 8);
    assert(mult(8, 2) == 5);
}
