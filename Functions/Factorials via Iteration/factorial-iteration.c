#include <stdio.h>
#include <assert.h>

static inline int fact(int a);

int main(void)
{
    assert(fact(4) == 24);
    assert(fact(1) == 1);
    assert(fact(0) == 1);
    assert(fact(10) == 3628800);
    assert(fact(3) == 6);
    return 0;
}

int fact(int a)
{
    int i;
    int tot = 1;

    for (i = 1; i <= a; i++) {
        tot *= i;
    }

    return tot;
}
