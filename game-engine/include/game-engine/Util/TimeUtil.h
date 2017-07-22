#ifndef _TIMEUTIL_H
#define _TIMEUTIL_H

#include <ctime>

float timeInSeconds()
{
    return (float)clock() / (float)CLOCKS_PER_SEC;
}

#endif /* _TIMEUTIL_H */
