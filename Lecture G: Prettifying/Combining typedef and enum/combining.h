#ifndef COMBINING_H
#define COMBINING_H

#include <stdio.h>
#include <assert.h>

enum day {sun, mon, tue, wed, thu, fri, sat};
typedef enum day day;

day find_next_day(day d);


#endif //COMBINING_H
