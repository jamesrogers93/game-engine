#ifndef _CAMERAABSTRACTFACTORY_H
#define _CAMERAABSTRACTFACTORY_H

class CameraAbstract;

class CameraAbstractFactory
{
public:
    CameraAbstractFactory()
    {}
    
    ~CameraAbstractFactory()
    {}
    
    CameraAbstract* createCamera() = 0;
    
};

#endif /* _CAMERAABSTRACTFACTORY_H */
