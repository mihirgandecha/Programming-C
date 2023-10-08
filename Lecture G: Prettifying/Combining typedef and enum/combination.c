#include "combining.h"


day find_next_day(day d)
{
    day next_day;
    switch (d)
    {
    case sun:
        next_day = mon;
        break;
    case mon:
        next_day = tue;
        break;
    case tue:
        next_day = wed;
        break;
    case wed:
        next_day = thu;
        break;
    case thu:
        next_day = fri;
        break;
    case fri:
        next_day = sat;
        break;
    case sat:
        next_day = sun;
        break;
    default:
        printf("I wasn't expecting that!\n");
        break;
    }
    return next_day;
}

int main(void)
{
    assert(find_next_day(mon) == tue);
    assert(find_next_day(tue) == wed);
    assert(find_next_day(wed) == thu);
    assert(find_next_day(thu) == fri);
    assert(find_next_day(fri) == sat);
    assert(find_next_day(sat) == sun);
    assert(find_next_day(sun) == mon);
    
    return 0;
}

