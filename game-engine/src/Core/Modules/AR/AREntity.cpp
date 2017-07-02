
// Game Engine AR
#include "game-engine/Core/Modules/AR/AREntity.h"
#include "game-engine/Core/Modules/AR/AR.h"
#include "game-engine/Core/Modules/AR/ARTracker.h"

// Game Engine Device
#include "game-engine/Core/Device/CameraCapture.h"

AREntity::AREntity(const std::string &name) : ENode(name)
{
    this->tracker = new ARTracker();
}

void AREntity::initialise()
{
    tracker->initalise();
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

void AREntity::frameRecieved(unsigned char *data, const float &width, const float &height, const float &padding)
{
    
}
