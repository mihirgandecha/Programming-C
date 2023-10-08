#ifndef FEVER_H
#define FEVER_H

enum tscale {celsius, farenheit};
typedef enum tscale tscale;
typedef double temperature;

// Argument 1 is temperature
// Argument 2 is scale (0=>Celsius, 1=>Farenheit)

bool fvr(double t, tscale s);

#endif // FEVER_H
