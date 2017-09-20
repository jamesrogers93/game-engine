#ifndef _CAMERAIOSFACTORY_H
#define _CAMERAIOSFACTORY_H

#include "game-engine/Peripherals/CameraAbstractFactory.h"

class CameraIOSFactory : public CameraAbstractFactory
{
public:
    CameraIOSFactory() : CameraAbstractFactory()
    {}
    
    ~CameraIOSFactory()
    {}
    
    CameraAbstract* createCamera()
    {
        return new CameraCapture();
    }
    
};

#endif /* _CAMERAIOSFACTORY_H */
