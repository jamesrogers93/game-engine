#include "game-engine/Modules/Animation/JointTransform.h"

const JointTransform JointTransform::interpolate(const float &progression, const JointTransform* jointTransform1, const JointTransform* jointTransform2)
{
    // Interpolate position linearly
    glm::vec4 position =  glm::mix(jointTransform1->getPosition(), jointTransform2->getPosition(), progression);
    
    // Interpolate rotation using SLERP
    glm::fquat rotation = glm::slerp(jointTransform1->getRotation(), jointTransform2->getRotation(), progression);
    
    return JointTransform(position, rotation);
}
