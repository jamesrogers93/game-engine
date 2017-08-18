
// Game Engine AR
#include "game-engine/Modules/AR/AREntity.h"
#include "game-engine/Modules/AR/AR.h"
#include "game-engine/Modules/AR/ARTracker.h"

// Game Engine Device
#include "game-engine/Device/CameraCapture.h"
#include "game-engine/Device/Gyroscope.h"

// STD
#include <iostream>

// GLM
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

AREntity::AREntity(const std::string &name) : Entity(name, Entity::AR_TRACKER)
{
    this->tracker = new ARTracker();
}

AREntity::~AREntity()
{
    CameraCapture::getInstance().removeDelegate(this);
    
    AR::getInstance().removeAREntity(name);
}

void AREntity::initialise()
{
    AR::getInstance().addAREntity(this->name, this);
    
    tracker->initialise();
}

void AREntity::deinitialise()
{
    AR::getInstance().removeAREntity(this->name);
    
    //tracker->deinitialise();
}

void AREntity::startCapture()
{
    CameraCapture::getInstance().startCapture();
}

void AREntity::stopCapture()
{
    CameraCapture::getInstance().stopCapture();
}

void AREntity::startTracking()
{

    glm::vec3 position(0.0, 0.0, 100.0);
    glm::fquat orientation;
    
    // Start the tracker
    this->tracker->start(position, orientation);
}

void AREntity::stopTracking()
{
    this->tracker->stop();
}

glm::mat4 AREntity::getCameraProjection(const float &nearPlane, const float &farPlane)
{
    return this->tracker->getCameraProjection(nearPlane, farPlane);
}

void AREntity::draw()
{
    CameraCapture::getInstance().display();
}

void AREntity::frameRecieved(unsigned char *data, const float &width, const float &height, const float &padding)
{
    //if(tracker->getState() != ARTracker::TRACKING)
    //{
    //    return;
    //}
    
    // Get gyroscope orientation
    Gyroscope *gyro = &Gyroscope::getInstance();
    glm::fquat gyroOrientation = gyro->getOrientation();
    
    // This just rotates the node according to the gyroscope orientation. Good for VR
    //this->rotateOW(glm::inverse(gyroOrientation));
    
    // Set the orientation on the tracker
    tracker->setOrientation(gyroOrientation);
    
    // Tracker the object
    if(!tracker->processFrame(data, width, height, padding))
    {
        return;
    }
    
    if(tracker->isTracking())
    {
        
        // Get position and orientation
        glm::vec3 position = tracker->getPosition();
        glm::fquat orientation = tracker->getOrientation();
        
        // Turn into right hand coordinates
        position.y = -position.y;
        position.z = -position.z;
        
        //printf("Position x: %f, y: %f, z %f \n", position.x, position.y, position.z);
        //printf("Rotation x: %f, y: %f, z %f, w %f \n", orientation.x, orientation.y, orientation.z, orientation.w);
        
        // Inverse the position
        glm::vec3 inversePosition = -position;
        
        // Transform node by translating first by the inverse of the tracker point, then rotating it by the inverse of the devices orientation.
        this->translateOW(inversePosition);
        this->rotateOW(glm::inverse(orientation), 1);
    }
    else
    {
        printf("Not tracking\n");
    }
    
}


