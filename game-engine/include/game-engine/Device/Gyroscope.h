#ifndef _GYROSCOPE_H
#define _GYROSCOPE_H

#include <glm/gtc/quaternion.hpp>

class Gyroscope
{
public:
    
    static Gyroscope& getInstance()
    {
        static Gyroscope instance;
        return instance;
    }
    
    void initialise();
    void deinitialise();
    
    glm::dquat getOrientation();
    
private:
    
    Gyroscope();
    ~Gyroscope();
    
    void *self;
};

#endif /* _GYROSCOPE_H */
