#include "game-engine/Core/Modules/AR/ARTracker.h"

#import <KudanCV/KudanCV.h>

ARTracker::ARTracker() : state(UNINITALISED)
{
}

void ARTracker::initalise()
{
    if(state == UNINITALISED)
    {
        this->tracker = new KudanArbiTracker();
    
        KudanCameraParameters parameters;
    
        // Should use the camera to get the image stream size, but it's not initialised yet, so just hardcode for now
        parameters.setSize(640, 480);
    
        // Don't know the intrinsics so tell it to figure them out
        parameters.guessIntrinsics();
    
        // Important: set the intrinsic parameters on the tracker
        tracker->setCameraParameters(parameters);
    
        std::string key = "Y+TzM9lcb0EfiJxoEqEvLaOaAWMjtdvFiiO1av2Sjkxboj886KE1wJsruv3kJvVHKSWy6KUEQPeMrKAX5uuCQUuccbPErjQuYklwfpH0SdicLuUoEJvKy0KOGjlJO6sUtNgb+XOjJWRIfVB6TpfRKvXkEYcKE+iRA4CMJp5vj3BVkrrtNXjZh7obKUSEDZpPQKZi0KDsr6SQSoCzjTnwgW1+j4/71A260mYLWyMe4OF1uQU7wMyON1ToMpkFLJipkEe7S+4I68Cq9c7W6RArOJbUYjHPLfKrO7zpYpDt+vy8/xuc//nZKFlG4zJhiIoqjyvfrU5CeoSO7O2KZv/CfAJxqnRt/wBB+ju49VVacWUoFG8t/0MPRlaE8Yyjz+jgt6u0UQwB8AK3j+4qloEVCqav4PafjCnDcwBOGHNMFv72zcZyKgOGLFTNRVRXpTP02Z67Jh0POfZfRdV4Gl+jvT49rYzpzuEMkbfR2pqwIIu38HCYhLw6V3qeH/JqUif/n2IlPZglT35wDwDvtWBHWpzpW6ct/RzMjjf8Pfa79kPoBUCQpOPRFV9uDCfqYPVMN7/zRZtxauO+1wMgTJxzd4MjOF0wBYZcHRWw1WG9A/NT+FnhhZrHMjJgEVReVK08x1ubIkfqYJKPrD2/PmYNVBI0mGnGS9QO3v81Y0NDVrY=";
    
        tracker->setApiKey(key);
        
        state = INITIALISED;
    }
}

void ARTracker::setOrientation(const glm::fquat &orientaton)
{
    if(state != UNINITALISED)
    {
        this->tracker->setSensedOrientation(KudanQuaternion(orientaton.x, orientaton.y, orientaton.z, orientaton.w));
    }
    else
    {
        // Log
    }
}

void ARTracker::start(const glm::vec3 &position, const glm::fquat &orientation)
{
    if(state == INITIALISED)
    {
        KudanVector3 startPosition(position.x, position.y, position.z);
        KudanQuaternion startOrientation(orientation.x, orientation.y, orientation.z, orientation.w);
        tracker->start(startPosition, startOrientation);
        
        state = TRACKING;
    }
}

void ARTracker::stop()
{
    if(state == TRACKING)
    {
        tracker->stop();
        
        state = INITIALISED;
    }
}

bool ARTracker::processFrame(unsigned char *data, const float &width, const float &height, const float &padding)
{
    if(state == TRACKING)
    {
        return tracker->processFrame(data, width, height, 1 , padding, false);
    }
    
    return false;
}

bool ARTracker::isTracking()
{
    return tracker->isTracking();
}

glm::mat3 ARTracker::getCameraIntrictics()
{
    if(state != UNINITALISED)
    {
        KudanMatrix3 K = tracker->getCameraMatrix();
    
        glm::mat3 K1;
        K1[0][0] = K(0,0);
        K1[0][1] = K(0,1);
        K1[0][2] = K(0,2);
    
        K1[1][0] = K(1,0);
        K1[1][1] = K(1,1);
        K1[1][2] = K(1,2);
    
        K1[2][0] = K(2,0);
        K1[2][1] = K(2,1);
        K1[2][2] = K(2,2);
    
        return K1;
    }
    return glm::mat3();
}

glm::mat3 ARTracker::getCameraProjection(const float &nearPlane, const float &farPlane)
{
    if(state != UNINITALISED && tracker->hasCameraCalibration())
    {
        KudanMatrix4 P = tracker->getProjectionMatrix(nearPlane, farPlane);
        
        glm::mat4 P1;
        P1[0][0] = P(0,0);
        P1[0][1] = P(0,1);
        P1[0][2] = P(0,2);
        P1[0][3] = P(0,3);
        
        P1[1][0] = P(1,0);
        P1[1][1] = P(1,1);
        P1[1][2] = P(1,2);
        P1[1][3] = P(1,3);
        
        P1[2][0] = P(2,0);
        P1[2][1] = P(2,1);
        P1[2][2] = P(2,2);
        P1[2][3] = P(2,3);
        
        P1[3][0] = P(3,0);
        P1[3][1] = P(3,1);
        P1[3][2] = P(3,2);
        P1[3][3] = P(3,3);
        
        return P1;
        
    }
    return glm::mat4();
}

glm::vec3 ARTracker::getPosition()
{
    KudanVector3 p;
    
    if(state == TRACKING)
    {
        p = tracker->getPosition();
    }
    
    return glm::vec3(p.x, p.y, p.z);
}

glm::fquat ARTracker::getOrientation()
{
    KudanQuaternion o;
    
    if(state == TRACKING)
    {
        o = tracker->getOrientation();
    }
    
    return glm::fquat(o.w, o.x, o.y, o.z);
}

