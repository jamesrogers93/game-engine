#ifndef _JOINTENTITY_H
#define _JOINTENTITY_H

#include "game-engine/Entity/Entity.h"

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
    
    const glm::mat4& getInverseBindPose() const { return this->mInverseBindPose; }
};

#endif /* _JOINTENTITY_H */
