#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "fiver.h"

#define FEVERTHRESHOLD 37.5

int main(void)
{
    assert(fvr(37.5, celsius) == true);
    assert(fvr(36.5, celsius) == false);
    assert(fvr(99.5, farenheit) == true);  
    assert(fvr(96.5, farenheit) == false);
    return 0;
}

bool fvr(double t, tscale s)
{
    // Assert to ensure that s is either celsius or farenheit.
    assert((s == celsius) || (s == farenheit));

    // If the scale is farenheit, convert the temperature to Celsius for comparison.
    if (s == farenheit) {
        t = (t - 32.0) * 5.0/9.0;
    }

    // Check if the temperature is above or equal to the fever threshold.
    return t >= FEVERTHRESHOLD;
}

