#include "game-engine/Core/GL/GLTexture.h"

#include "game-engine/Defines/OpenGL.h"

GLTexture GLTexture::loadFromData(const Texture &texture)
{
    if (!texture.getData())
    {
        return GLTexture(0);
    }
    
    GLuint textureId;
    
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Create texture and generate mipmaps
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 texture.getWidth(),
                 texture.getHeight(),
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 texture.getData());
    
    glGenerateMipmap(GL_TEXTURE_2D);
    
    return GLTexture(textureId);
}
