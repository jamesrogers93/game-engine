#ifndef _PHYSICSSHAPE_H
#define _PHYSICSSHAPE_H

// Bullet
//#include <btBulletCollisionCommon.h>

class btCollisionShape;

class PhysicsShape
{
public:
    PhysicsShape()
    {}
    
    btCollisionShape *shape;
};

#endif /* _PHYSICSSHAPE_H */
