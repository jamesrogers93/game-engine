#ifndef _TEXTUREUTIL_H
#define _TEXTUREUTIL_H

#include <string>

class Texture
{
private:
    
    unsigned char *data;
    int width;
    int height;
    int stride;
    
public:
    
    Texture()
    : data(NULL), width(0), height(0), stride(0)
    {}
    
    Texture(unsigned char* data, const int &width, const int &height, const int &stride)
    : data(data), width(width), height(height), stride(stride)
    {}
    
    static bool loadFromFile(Texture &texture, const std::string &file);
    
    const unsigned char* getData() const { return data; }
    const int& getWidth() const { return width; }
    const int& getHeight() const { return height; }
    const int& getStride() const { return stride; }
    
};

#endif /* _TEXTUREUTIL_H */
