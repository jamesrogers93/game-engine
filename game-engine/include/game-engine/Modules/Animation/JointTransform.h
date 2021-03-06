#ifndef _JOINTTRANSFORM_H
#define _JOINTTRANSFORM_H

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class JointTransform
{
public:
    
    JointTransform(const glm::vec4 &position, const glm::fquat &rotation) : mPosition(position), mRotation(rotation)
    {}
    
    const glm::vec4& getPosition() const { return this->mPosition; }
    const glm::fquat& getRotation() const { return this->mRotation; }
    
    static const JointTransform interpolate(const float &progression, const JointTransform* jointTransform1, const JointTransform* jointTransform2);
    
private:
    glm::vec4 mPosition;
    glm::fquat mRotation;
};

#endif /* _JOINTTRANSFORM_H */
