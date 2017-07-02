#ifndef _ARENTITY_H
#define _ARENTITY_H

// STD
#include <string>

// Game Engine
#include "game-engine/Core/Entity/ENode.h"

// Game Engine Device
#include "game-engine/Core/Device/CameraCapture.h"

class ARTracker;

class AREntity : public ENode, public CameraCaptureDelegate
{
private:
    
public:
    AREntity(const std::string &name);
    
    void initialise();
    
    void startCapture();
    void stopCapture();
    
    void draw();
    
    void frameRecieved(unsigned char *data, const float &width, const float &height, const float &padding);
    
protected:
    
    ARTracker *tracker;
    
    void attachToEngine();
};

#endif /* _ARENTITY_H */
