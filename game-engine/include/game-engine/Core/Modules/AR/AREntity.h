#ifndef _ARENTITY_H
#define _ARENTITY_H

// STD
#include <string>

// Game Engine
#include "game-engine/Core/Entity/ENode.h"

class AREntity : public ENode
{
private:
    
public:
    AREntity(const std::string &name);
    
    void startCapture();
    void stopCapture();
    
    void draw();
    
protected:
    void attachToEngine();
};

#endif /* _ARENTITY_H */
