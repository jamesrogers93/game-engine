#ifndef _JOINTTRANSFORM_H
#define _JOINTTRANSFORM_H

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class JointTransform
{
public:
    JointTransform()
    {}
    
    JointTransform(const glm::vec3 &position, const glm::fquat &rotation) : mPosition(position), mRotation(rotation)
    {}
    
    const glm::vec3& getPosition() const { return this->mPosition; }
    const glm::fquat& getRotation() const { return this->mRotation; }
    
private:
    glm::vec3 mPosition;
    glm::fquat mRotation;
};

#endif /* _JOINTTRANSFORM_H */
