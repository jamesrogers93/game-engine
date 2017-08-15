#include "game-engine/Modules/Physics/PhysicsSphere.h"

// Bullet
#include <btBulletCollisionCommon.h>

PhysicsSphere::PhysicsSphere(const float &radius) : PhysicsShape()
{
    shape = new btSphereShape(radius);
}
