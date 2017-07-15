#ifndef _GRAPHICSREAD_H
#define _GRAPHICSREAD_H

#include <string>
#include <fstream>

class GraphicsRead
{
public:
    static bool readJMPFile(const std::string &filePath);
    
private:
    static const std::string GEOMETRY_TYPE;
    
    static void readGeometry(std::ifstream &file);
};

#endif /* _GRAPHICSREAD_H */
