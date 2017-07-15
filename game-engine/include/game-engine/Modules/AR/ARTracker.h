#ifndef _ARTRACKER_H
#define _ARTRACKER_H

// GLM
#include <glm/gtx/quaternion.hpp>

class KudanArbiTracker;

class ARTracker
{
private:
    enum State { UNINITALISED, INITIALISED, TRACKING};
    State state;
    
public:
    ARTracker();
    
    void initalise();
    
    void setOrientation(const glm::fquat &orientaton);
    
    void start(const glm::vec3 &position, const glm::fquat &orientation);
    void stop();
    
    bool processFrame(unsigned char *data, const float &width, const float &height, const float &padding);
    
    bool isTracking();
    
    glm::mat3 getCameraIntrictics();
    glm::mat3 getCameraProjection(const float &nearPlane, const float &farPlane);
    glm::vec3 getPosition();
    glm::fquat getOrientation();
    
private:
    
    KudanArbiTracker *tracker;
    
};

#endif /* _ARTRACKER_H */
