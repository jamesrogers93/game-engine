#ifndef _JOINTENTITY_H
#define _JOINTENTITY_H

#include "game-engine/Entity/Entity.h"

#include <glm/glm.hpp>

class JointEntity : public Entity
{
private:
    
    //glm::mat4 mlocalBindPose;
    glm::mat4 mInverseBindPose;

public:
    JointEntity(const std::string &name) : Entity(name, Entity::JOINT)
    {}

    void initialise() {}
    void update() {}
    
    //void setLocalBindPose(const glm::mat4 localBindPose) { this->mlocalBindPose = localBindPose;
    
        //this->transformOW(inverseBindPose);
    //}
    
    //const glm::mat4& getLocalBindPose() const { return this->mlocalBindPose; }
    const glm::mat4& getInverseBindPose() const { return this->mInverseBindPose; }
};

#endif /* _JOINTENTITY_H */
