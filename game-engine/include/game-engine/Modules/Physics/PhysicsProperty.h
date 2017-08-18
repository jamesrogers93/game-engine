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
    std::function<void(PhysicsProperty*)> beforeCollisionTestCallback;
    
    unsigned short collisionMask;
    unsigned short collidesWithMask;
    bool maskSet;
    
    PhysicsProperty(const std::string &name, PhysicsShape* shape);
    ~PhysicsProperty();
    
    bool makeActive();
    bool makeUnactive();
    
    const int getCollisionFlags();
    
    std::function<void(PhysicsProperty*, PhysicsProperty*, btManifoldPoint*)> getCollisionCallback() { return collisionCallback; }
    std::function<void(PhysicsProperty*)> getBeforeCollisionTestCallback() { return beforeCollisionTestCallback; }
    
    bool getIsMaskSet() { return maskSet;  }
    unsigned short getCollisionMask() { return collisionMask; }
    unsigned short getCollidesWithMask() { return collidesWithMask; }
    
    void setWorldTransform(const glm::vec3 &transform);
    void setCollisionFlags(const int flags);
    void setCollisionCallback(const std::function<void(PhysicsProperty*, PhysicsProperty*, btManifoldPoint*)> collisionCallback) { this->collisionCallback = collisionCallback; }
    void setBeforeCollisionTestCallback(const std::function<void(PhysicsProperty*)> callback) { this->beforeCollisionTestCallback = callback; }
    
    void setMask(unsigned short collisionMask, unsigned short collidesWithMask)
    { this->collisionMask = collisionMask; this->collidesWithMask = collidesWithMask; maskSet = true; }
};

#endif /* _PHYSICSPROPERTY_H */
