#ifndef _ARENTITY_H
#define _ARENTITY_H

// STD
#include <string>

// Game Engine
#include "game-engine/Core/Entity/ENode.h"

// Game Engine defines
#include "game-engine/Defines/CameraCapture.h"

class AREntity : public ENode
{
private:
    CameraCapture capture;
    
public:
    AREntity(const std::string &name);
    
    bool initalise();
    void deinitalise();
    
    void startCapture();
    void stopCapture();
    
    CameraCapture& getCameraCapture() {   return this->capture;   }
    
protected:
    void attachToEngine();
};

#endif /* _ARENTITY_H */
