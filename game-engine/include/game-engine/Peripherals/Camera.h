#ifndef _CAMERA_H
#define _CAMERA_H

#include "game-engine/Peripherals/CameraAbstractFactory.h"

class CameraAbstract;

class Camera
{
public:
    
    Camera()
    {
        CameraAbstractFactory *factory = NULL;
        
        #ifdef IOS
            factory = new CameraIOSFactory();
        #endif
        
        if(factory != NULL)
        {
            mCameraPtr = factory->createCamera();
        }
    }
    
    ~Camera()
    {}
    
    CameraAbstract *mCameraPtr;
};

#endif /* _CAMERA_H */
