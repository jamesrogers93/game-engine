#ifndef _PHYSICSPROPERTY_H
#define _PHYSICSPROPERTY_H

// STD
#include <string>
#include <functional>

// GLM
#include <glm/glm.hpp>

#include "game-engine/Entity/Property.h"


class PhysicsShape;
class btCollisionObject;
class btManifoldPoint;

class PhysicsProperty : public Property
{
public:
    
    PhysicsShape *mShape;
    btCollisionObject* collisionObject;
    std::function<void(PhysicsProperty*, PhysicsProperty*, btManifoldPoint*)> collisionCallback;
    
    PhysicsProperty(const std::string &name, PhysicsShape* shape);
    
    bool makeActive();
    bool makeUnactive();
    
    const int getCollisionFlags();
    
    void callback(PhysicsProperty* objA, PhysicsProperty* objB, btManifoldPoint* pt)
        { collisionCallback(objA, objB, pt); }
    
    void setWorldTransform(const glm::vec3 &transform);
    void setCollisionFlags(const int flags);
    void setCollisionCallback(const std::function<void(PhysicsProperty*, PhysicsProperty*, btManifoldPoint*)> collisionCallback) { this->collisionCallback = collisionCallback; }
};

#endif /* _PHYSICSPROPERTY_H */
