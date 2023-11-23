#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define NMBRS 1000000

int bin_rec(int k, const int* a, int l, int r);

int main(void)
{
    int a[NMBRS];
    srand(time(NULL));

    // Put even numbers into array
    for (int i = 0; i < NMBRS; i++) {
        a[i] = 2 * i;
    }

    // Domany searches for a random number
    for (int i = 0; i < 10 * NMBRS; i++) {
        int n = rand() % NMBRS;
        if ((n % 2) == 0) {
            assert(bin_rec(n, a, 0, NMBRS - 1) == n / 2);
        }
        else {
            // No odd numbers in this list
            assert(bin_rec(n, a, 0, NMBRS - 1) < 0);
        }
    }

    return 0;
}

int bin_it(int target, const int* array, int index_start, int pos_end)
{
    while (index_start <= pos_end) {
        int midpoint = (index_start + pos_end) / 2;
        if (target == array[midpoint]) {
            return midpoint;
        } else {
            if (target > array[midpoint]) {
                index_start = midpoint + 1;
            } else {
                pos_end = midpoint - 1;
            }
        }
    }
    return -1;
}

int bin_rec(int k, const int* a, int l, int r)
{
    if (l > r)
        return -1;

    int m = (l + r) / 2;

    if (k == a[m]) {
        return m;
    } else {
        //if more than midpoint, bin the beginning to midpoint
        if (k > a[m]) {
            return bin_rec(k, a, m + 1, r);
        } else {
            return bin_rec(k, a, l, m - 1);
        }
    }
}
