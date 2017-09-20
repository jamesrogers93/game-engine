#ifndef _PHYSICSPHERE_H
#define _PHYSICSPHERE_H

#include "game-engine/Modules/Physics/PhysicsShape.h"

class PhysicsSphere : public PhysicsShape
{
public:
    PhysicsSphere(const float &radius);
};

#endif /* _PHYSICSPHERE_H */
