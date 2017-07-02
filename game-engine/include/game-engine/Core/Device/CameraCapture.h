
#ifndef _CAMERACAPTURE_H
#define _CAMERACAPTURE_H

// STD
#include <string>

// OpenGL
#include "game-engine/Defines/OpenGL.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader;
class Geometry;

class CameraCapture
{
public:
    
    enum Resolution
    {
        RES_NOT_SET, RES_640x480, RES_1280x720, RES_1920x1080
    };
    static const Resolution DEFAULT_RES;
    static const std::string SHADER_VERTEX;
    static const std::string SHADER_FRAGMENT;
    static const std::string SHADER_LUMA_NAME;
    static const std::string SHADER_CHROMA_NAME;
    static const std::string SHADER_MODEL_NAME;
    
    static CameraCapture& getInstance()
    {
        static CameraCapture instance;
        return instance;
    }
    
    bool initialise();
    void deinitialise();
    
    void startCapture();
    void stopCapture();
    
    void display();
    
    void bindTextures();
    
    GLuint getLumaTextureID();
    GLuint getChromaTextureID();
    
    glm::mat4& getScale() { return this->scale; }
    
    void setResolution(const Resolution &res) {this->res = res;}
    Resolution getResolution() {    return res;    }
    
    bool isInitialised() {   return this->initialised;   }
    bool isCapturing()  { return this->capturing;   }
    
private:
    
    CameraCapture();
    ~CameraCapture();
    
    CameraCapture(CameraCapture const&);        // Don't Implement
    void operator=(CameraCapture const&);		// Don't implement
    
    bool initialiseCamera();
    void initialiseView();
    
    Resolution res;
    bool initialised;
    bool capturing;
    unsigned int cameraWidth, cameraHeight;
    glm::mat4 scale;
    
    Shader *shader;
    Geometry *geometry;
    
    void *self;
    
    
};

#endif /* _CAMERACAPTUREINTERFACEIOS_H */
