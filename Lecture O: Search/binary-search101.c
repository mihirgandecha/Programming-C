#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define NMBRS 1000000

int bin_it(int target, const int* array, int index_start, int pos_end);

int main(void)
{
    int array[NMBRS];
    srand(time(NULL));

    // Put even numbers into array
    for (int counter_even = 0; counter_even < NMBRS; counter_even++) {
        array[counter_even] = 2 * counter_even;
    }

    // Domany searches for array random number
    for (int counter_odd = 0; counter_odd < 10 * NMBRS; counter_odd++) {
        int n = rand() % NMBRS;
        if ((n % 2) == 0) {
            assert(bin_it(n, array, 0, NMBRS - 1) == n / 2);
        }
        else {
            // No odd numbers in this list
            assert(bin_it(n, array, 0, NMBRS - 1) < 0);
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
