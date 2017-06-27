#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "game-engine/Defines/OpenGL.h"

class Texture
{
public:
    Texture(const GLuint &textureID) : textureID(textureID) {}
    ~Texture(){}
    
    const GLuint& getTextureID()    {   return this->textureID; }
    
private:
    GLuint textureID;
};

#endif /* _TEXTURE_H */
