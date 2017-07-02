
// Game Engine AR
#include "game-engine/Core/Modules/AR/AREntity.h"
#include "game-engine/Core/Modules/AR/AR.h"

// Game Engine Device
#include "game-engine/Core/Device/CameraCapture.h"

AREntity::AREntity(const std::string &name) : ENode(name)
{
    
}

void AREntity::attachToEngine()
{
    AR::getInstance().addAREntity(this->name, this);
}

void AREntity::startCapture()
{
    CameraCapture::getInstance().startCapture();
}

void AREntity::stopCapture()
{
    CameraCapture::getInstance().stopCapture();
}

void AREntity::draw()
{
    CameraCapture::getInstance().display();
}
