#ifndef _ARVIEW_H
#define _ARVIEW_H

// STD
#include <string>
#include <map>

// OpenGL
#include "game-engine/Defines/OpenGL.h"

class Shader;
class Geometry;

class ARView
{
private:
    static const std::string SHADER_VERTEX;
    static const std::string SHADER_FRAGMENT;
    static const std::string SHADER_LUMA_NAME;
    static const std::string SHADER_CHROMA_NAME;
    
    Shader *shader;
    Geometry *geometry;
    
    unsigned int width, height;
    
    std::map<std::string, GLint> uniforms;
    
public:
    ARView();
    
    void initalise(const unsigned int &screenWidth, const unsigned int &screenHeight);
    void deinitialise();
    void draw();
};

#endif /* _ARVIEW_H */
