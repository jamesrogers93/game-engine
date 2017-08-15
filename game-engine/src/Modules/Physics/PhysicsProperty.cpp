#include "game-engine/Modules/Physics/PhysicsProperty.h"
#include "game-engine/Modules/Physics/PhysicsShape.h"
#include "game-engine/Modules/Physics/Physics.h"

// Bullet
#include <btBulletCollisionCommon.h>

PhysicsProperty::PhysicsProperty(const std::string &name, PhysicsShape* shape) : Property(name, Property::PHYSICS), mShape(shape), maskSet(false)
{
    collisionObject = new btCollisionObject();
    collisionObject->setUserPointer(this);
    collisionObject->setCollisionShape(shape->shape);
}

bool PhysicsProperty::makeActive()
{
    this->mActive = true;
    
    return Physics::getInstance().addPhysicsProperty(this->mName, this);
}

bool PhysicsProperty::makeUnactive()
{
    this->mActive = false;

    return Physics::getInstance().removePhysicsProperty(this->mName);
}

const int PhysicsProperty::getCollisionFlags()
{
    return collisionObject->getCollisionFlags();
}

void PhysicsProperty::setCollisionFlags(const int flags)
{
    collisionObject->setCollisionFlags(flags);
}

void PhysicsProperty::setWorldTransform(const glm::vec3 &transform)
{
    collisionObject->getWorldTransform().setOrigin(btVector3((btScalar) transform.x, (btScalar) transform.y, (btScalar) transform.z));
}
