#ifndef _STRINGUTIL_H
#define _STRINGUTIL_H

#include <string>

inline std::string toLower(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

inline std::string fileName(const std::string &path, const bool &withExtension = true)
{
    size_t found;
    found = path.find_last_of("/\\");
    
    std::string file = path.substr(found+1);
    
    if(withExtension)
    {
        return file;
        
    } else
    {
        found = file.find_last_of(".");
        
        return file.substr(0, found);
    }
}



#endif /* _STRINGUTIL_H */
