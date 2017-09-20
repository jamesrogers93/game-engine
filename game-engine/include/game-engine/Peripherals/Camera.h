#ifndef _CAMERA_H
#define _CAMERA_H

// STD
#include <string>
#include <vector>

#include "game-engine/Peripherals/CameraAbstract.h"
#include "game-engine/Peripherals/CameraAbstractFactory.h"

// OpenGL
#include "game-engine/Core/GL/OpenGL.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Game Engine Core
#include "game-engine/Core/Utilities/DispatchQueue.h"

class CameraAbstract;
class Shader;
class MeshGL;

class CameraCaptureDelegate
{
public:
    virtual void frameRecieved(unsigned char *data, const float &width, const float &height, const float &padding) = 0;
};

class Camera
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
    
    static Camera& getInstance()
    {
        static Camera instance;
        return instance;
    }
    
    CameraAbstract *mCameraPtr;
    
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
    
    void addDelegate(CameraCaptureDelegate* delegate);
    void removeDelegate(CameraCaptureDelegate* delegate);
    
    void callDelegates(unsigned char *data, const float &width, const float &height, const float &padding);
    
private:
    
    Camera();
    ~Camera();
    
    Camera(Camera const&);        // Don't Implement
    void operator=(Camera const&);		// Don't implement
    
    
    bool initialiseCamera();
    void initialiseView();
    
    Resolution res;
    bool initialised;
    bool capturing;
    unsigned int cameraWidth, cameraHeight;
    glm::mat4 scale;
    
    Shader *shader;
    MeshGL *geometry;
    
    std::vector<CameraCaptureDelegate*> delegates;
    
    DispatchQueue delegateDispatchQueue;
};

#endif /* _CAMERA_H */
