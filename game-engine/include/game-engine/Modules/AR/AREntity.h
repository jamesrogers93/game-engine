#ifndef _ARENTITY_H
#define _ARENTITY_H

// STD
#include <string>

// Game Engine
#include "game-engine/Entity/Entity.h"

// Game Engine Device
#include "game-engine/Device/CameraCapture.h"

class ARTracker;

class AREntity : public Entity, public CameraCaptureDelegate
{
    
public:
    AREntity(const std::string &name);
    
    void initialise();
    //void update(){}
    
    void startCapture();
    void stopCapture();
    
    void startTracking();
    void stopTracking();
    
    glm::mat4 getCameraProjection(const float &nearPlane, const float &farPlane);
    
    void draw();
    
    void frameRecieved(unsigned char *data, const float &width, const float &height, const float &padding);
    
private:
    
    ARTracker *tracker;
};

#endif /* _ARENTITY_H */
