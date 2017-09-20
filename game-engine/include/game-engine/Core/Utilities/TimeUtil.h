#ifndef _TIMEUTIL_H
#define _TIMEUTIL_H

#include <time.h>

double timeSinceLastUpdate = 0.0;

double timeInSeconds()
{
    static clock_t start = clock();
    
    return (double)(clock() - start ) / (double) CLOCKS_PER_SEC;
    //return difftime(time(0), startTime);
}

#endif /* _TIMEUTIL_H */
