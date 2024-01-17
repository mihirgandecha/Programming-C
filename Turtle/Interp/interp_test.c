/*

Regression Testing: Running previous tests after changes are made
to ensure functionality still works.

Unit Testing!

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include "interp.h"

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)

static char * all_tests(void);
static char * test_setCol(void);

static char * all_tests(){
    mu_run_test(test_setCol);
    // Add more tests as needed...
    return 0;
}

static char * test_setCol() {
    Program* testTurtle = initTurtle();

    setCol(&testTurtle, "BLACK");
    mu_assert("error, turtle->colour != 'B'", testTurtle->colour == 'B');

    // setCol(&turtle, "WHITE");
    // mu_assert("error, turtle->colour != 'W'", turtle.colour == 'W');

    // setCol(&turtle, "RED");
    // mu_assert("error, turtle->colour != 'R'", turtle.colour == 'R');

    // ... repeat for other colors ...

    // setCol(&turtle, "INVALID_COLOR");
    // mu_assert("error, turtle->colour != 'W'", turtle.colour == 'W');
    free(turtle);
    return 0;
}