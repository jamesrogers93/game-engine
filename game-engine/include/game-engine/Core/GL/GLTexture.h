#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "game-engine/Defines/OpenGL.h"

#include "game-engine/Util/TextureUtil.h"

class GLTexture
{
private:
    GLuint textureID;
    
public:
    
    GLTexture(const GLuint &textureID = 0) : textureID(textureID) {}
    ~GLTexture(){}
    
    const GLuint& getTextureID() const {   return this->textureID; }
    
    static GLTexture loadFromData(const Texture &texture);
    
};

#endif /* _TEXTURE_H */
