
#ifndef _CAMERACAPTUREINTERFACEIOS_H
#define _CAMERACAPTUREINTERFACEIOS_H

// OpenGL
#include "game-engine/Defines/OpenGL.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CameraCapture
{
public:
    
    enum CameraFace {FRONT, BACK};
    CameraCapture(void);
    ~CameraCapture(void);
    
    int initialise(const CameraFace &face);
    void deinitialise(void);
    
    void startCapture(void);
    void stopCapture(void);
    
    void bindTextures(void);
    
    GLuint getLumaTextureID();
    GLuint getChromaTextureID();
    
    glm::mat4& getScale() { return this->scale; }
    
private:
    
    unsigned int cameraWidth, cameraHeight;
    glm::mat4 scale;
    
    void *self;
    
    
};

#endif /* _CAMERACAPTUREINTERFACEIOS_H */
