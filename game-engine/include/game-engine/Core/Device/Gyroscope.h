#ifndef _GYROSCOPE_H
#define _GYROSCOPE_H

#include <glm/glm.hpp>

class Gyroscope
{
public:
    
    static Gyroscope& getInstance()
    {
        static Gyroscope instance;
        return instance;
    }
    
    void initialise();
    
   // glm::quat getOrientation() {return glm::quat;}
    
private:
    
    Gyroscope();
    ~Gyroscope();
    
    void *self;
};

#endif /* _GYROSCOPE_H */
