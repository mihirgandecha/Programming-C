#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int bin_it(int k, const int* a, int l, int r);
int bin_rec(int k, const int* a, int l, int r);
int interp(int k, const int* a, int l, int r);
int* parse_args(int argc, char* argv[], int* n, int* srch);

void measure_execution_time(int (*search_function)(int, const int*, int, int), const int* a, int n, int srch, const char* search_name);

int main(int argc, char* argv[]) {
    int i, n, srch;
    int* a;
    int (*p[3])(int k, const int* a, int l, int r) = {bin_it, bin_rec, interp};
    const char* search_names[3] = {"Binary Search : Iterative", "Binary Search : Recursive", "Interpolation"};

    a = parse_args(argc, argv, &n, &srch);

    srand(time(NULL));
    for (i = 0; i < n; i++) {
        a[i] = 2 * i;
    }

    for (i = 0; i < 4; i++) {
        measure_execution_time(p[i], a, n, srch, search_names[i]);
    }

    free(a);
    return 0;
}

// Your search functions and parse_args function remain the same.

void measure_execution_time(int (*search_function)(int, const int*, int, int), const int* a, int n, int srch, const char* search_name) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int i = 0; i < 5000000; i++) {
        search_function(a[rand() % n], a, 0, n - 1);
    }
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("%s n=%d=%.2f\n", search_name, n, cpu_time_used);
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

int interp(int k, const int* a, int l, int r) {
    int m;
    double md;

    while (l <= r) {
        md = ((double)(k - a[l]) / (double)(a[r] - a[l]) * (double)(r - l)) + (double)(l);
        m = 0.5 + md;

        if (m > r || m < l) {
            return -1;
        }

        if (k == a[m]) {
            return m;
        } else {
            if (k > a[m]) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
    }

    return -1;
}

#include <stdio.h>
#include <stdlib.h>

int* parse_args(int argc, char* argv[], int* n, int* srch) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <srch>\n", argv[0]);
        exit(1);
    }

    *n = atoi(argv[1]);
    *srch = atoi(argv[2]);

    if (*n <= 0 || *srch < 0 || *srch > 2) {
        fprintf(stderr, "Invalid arguments. n must be a positive integer, srch must be 0, 1, or 2.\n");
        exit(1);
    }

    int* a = (int*)malloc(*n * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }

    return a;
}

