
// Game Engine AR
#include "game-engine/Core/Modules/AR/AREntity.h"
#include "game-engine/Core/Modules/AR/AR.h"
#include "game-engine/Core/Modules/AR/ARTracker.h"

// Game Engine Device
#include "game-engine/Core/Device/CameraCapture.h"
#include "game-engine/Core/Device/Gyroscope.h"

// STD
#include <iostream>

// GLM
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

AREntity::AREntity(const std::string &name, const glm::vec3 &position) : ENode(name, position)
{
    this->tracker = new ARTracker();
}

void AREntity::initialise()
{
    AR::getInstance().addAREntity(this->name, this);
    
    tracker->initalise();
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
    // Get position
   /* glm::vec3 position = glm::vec3(this->globalModel[3]);
    
    // Get orientation
    Gyroscope *gyro = &Gyroscope::getInstance();
    glm::fquat orientation = gyro->getOrientation();*/
    
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

static float degrees = 0.0f;
void AREntity::frameRecieved(unsigned char *data, const float &width, const float &height, const float &padding)
{
    /*
    // TEST
    //this->translateOW(0.0, 0.0, -10.0);
    //this->rotate(glm::radians(1.0f), glm::vec3(1.0, 0.0,0.0));
    
    glm::mat4 T = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0, 10.0));
    //glm::fquat Q = glm::angleAxis(glm::radians(degrees++), glm::vec3(1.0, 0.0,0.0));
    //Q = glm::normalize(Q);
    //glm::mat4 R = glm::mat4_cast(Q);
    
    glm::mat4 R = glm::rotate(glm::mat4(), glm::radians(degrees++), glm::vec3(1.0, 0.0, 0.0));
    this->localModel = R*T;
    if(degrees > 360.0f)
        degrees = 0.0f;
    // END TEST
    */
    
    
    
    Gyroscope *gyro = &Gyroscope::getInstance();
    
    glm::fquat gyroOrientation = gyro->getOrientation();
    //this->rotateOW(glm::inverse(gyroOrientation));
    //printf("Rotation before x: %f, y: %f, z %f, w %f \n", gyroOrientation.x, gyroOrientation.y, gyroOrientation.z, gyroOrientation.w);
    
    tracker->setOrientation(gyroOrientation);
    
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
        
        printf("Position x: %f, y: %f, z %f \n", position.x, position.y, position.z);
        //printf("Rotation x: %f, y: %f, z %f, w %f \n", orientation.x, orientation.y, orientation.z, orientation.w);
        
        // Use orientation of device to translate camera along
        
        
        // We want to translate it by the inverse of the position of the tracked point.
        // However, y seems to be reversed, so we only inverse x and z
        // Translate by direction vector
        //glm::vec3 newPosition = position * dir;
        glm::vec3 inversePosition = -position;
        //translateOW(inversePosition);
        
        // Also need to rotate the node by the inverse of the tracked point orientation.
        // May need to not inverse the y rotation?
        this->localModel = glm::mat4_cast(glm::inverse(orientation)) * glm::translate(glm::mat4(), inversePosition);
        //rotateOW(glm::inverse(orientation));
        
        // Test inverse x coord
        //translateOW(glm::vec3(position.x, position.y, position.z));
        //rotateOW(glm::radians(90.0f), glm::vec3(1.0, 0.0,0.0));
    }
    else
    {
        printf("Not tracking\n");
    }
    
}


