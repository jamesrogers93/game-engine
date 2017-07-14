#ifndef _JOINTENTITY_H
#define _JOINTENTITY_H

#include "game-engine/Core/Entity/ENode.h"

#include <glm/glm.hpp>

class JointEntity : public ENode
{
private:
    glm::mat4 mInverseBindPose;

public:
    JointEntity(const std::string &name) : ENode(name)
    {}

    void initialise() {}
    void update() {}
    
    void setInverseBindPose(const glm::mat4 inverseBindPose) { this->mInverseBindPose = inverseBindPose; }
    
};

#endif /* _JOINTENTITY_H */
