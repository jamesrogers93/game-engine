#include "game-engine/Core/Modules/AR/AREntity.h"

#include "game-engine/Core/Modules/AR/AR.h"

AREntity::AREntity(const std::string &name) : ENode(name)
{
    
}

void AREntity::attachToEngine()
{
    AR::getInstance().addAREntity(this->name, this);
}

bool AREntity::initalise()
{
    return this->capture.initialise(CameraCapture::FRONT);
}

void AREntity::deinitalise()
{
    this->capture.deinitialise();
}

void AREntity::startCapture()
{
    this->capture.startCapture();
}

void AREntity::stopCapture()
{
    this->capture.startCapture();
}
