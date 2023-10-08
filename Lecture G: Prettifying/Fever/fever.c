#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define FEVERTHRESHOLD 37.5

enum tscale {celsius, farenheit};
typedef enum tscale tscale;
typedef double temperature;

// Argument 1 is temperature
// Argument 2 is scale (0=>Celsius, 1=>Farenheit)

bool fvr(double t, tscale s);

int main(void)
{
    assert(fvr(37.5, celsius) == true);
    assert(fvr(36.5, celsius) == false);
    assert(fvr(96.5, farenheit) == false);
    assert(fvr(99.5, farenheit) == true);
    return 0;
}

bool fvr(double t, tscale s){
 
assert((s == celsius) || (s == farenheit));
if (s >= FEVERTHRESHOLD){
			t = (t-32.5) * 9.0/5.0;
}
			return false; //NO ELSE TO SAVE MEMORY
	return t;
}