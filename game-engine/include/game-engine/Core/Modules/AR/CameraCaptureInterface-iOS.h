
#ifndef _CAMERACAPTUREINTERFACEIOS_H
#define _CAMERACAPTUREINTERFACEIOS_H

#include "game-engine/Defines/OpenGL.h"

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
    
private:
    void *self;
    
    
};

#endif /* _CAMERACAPTUREINTERFACEIOS_H */
