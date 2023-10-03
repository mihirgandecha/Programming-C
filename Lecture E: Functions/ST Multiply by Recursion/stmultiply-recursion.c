/*Try towritemult(a,b)without using 2 anymaths cleverer than addition. */
#include <stdio.h>
#include <assert.h>

static inline int mult(int a, int b);
void test(void);

int main(void)
{
    test();

    return 0;
}

int mult(int a, int b)
{

    if (a == 0 ||b == 0) {
        return 0;
    }
    else{
        return (a + mult(a, b - 1));
    }


}

void test(void)
{
    assert(mult(5,3)==15);
    assert(mult(3,5)==15);
    assert(mult(0,3)==0);
    assert(mult(3,0)==0);
    assert(mult(1,8)==8);
    assert(mult(8,1)==8);
}
