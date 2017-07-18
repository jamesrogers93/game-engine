#ifndef _STRINGUTIL_H
#define _STRINGUTIL_H

#include <string>

inline std::string toLower(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

#endif /* _STRINGUTIL_H */
