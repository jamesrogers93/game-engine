#ifndef _JOINTENTITY_H
#define _JOINTENTITY_H

#include "game-engine/Core/Entity/Entity.h"

#include <glm/glm.hpp>

class JointEntity : public Entity
{
private:
    glm::mat4 mInverseBindPose;

public:
    JointEntity(const std::string &name) : Entity(name, Entity::JOINT)
    {}

    void initialise() {}
    void update() {}
    
    void setInverseBindPose(const glm::mat4 inverseBindPose) { this->mInverseBindPose = inverseBindPose; }
    
};

#endif /* _JOINTENTITY_H */
