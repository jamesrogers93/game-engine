#ifndef _ARENTITY_H
#define _ARENTITY_H

// STD
#include <string>

// Game Engine
#include "game-engine/Core/Main/Entity.h"

// Game Engine Device
#include "game-engine/Peripherals/CameraCapture.h"

class ARTracker;

class AREntity : public Entity, public CameraCaptureDelegate
{
    
public:
    AREntity(const std::string &name);
    ~AREntity();
    
    void initialise();
    void deinitialise();
    //void update(){}
    
    void startCapture();
    void stopCapture();
    
    void startTracking(const glm::vec3 &position);
    void stopTracking();
    
    glm::mat4 getCameraProjection(const float &nearPlane, const float &farPlane);
    
    void draw();
    
    void frameRecieved(unsigned char *data, const float &width, const float &height, const float &padding);
    
    ARTracker* getTracker() { return tracker; }
    
private:
    
    ARTracker *tracker;
};

#endif /* _ARENTITY_H */
