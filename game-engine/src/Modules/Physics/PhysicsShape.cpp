#include "game-engine/Modules/Physics/PhysicsShape.h"

// Bullet
#include <btBulletCollisionCommon.h>

PhysicsShape::~PhysicsShape()
{
    delete shape;
}
