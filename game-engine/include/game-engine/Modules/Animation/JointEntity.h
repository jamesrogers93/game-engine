#ifndef _JOINTENTITY_H
#define _JOINTENTITY_H

#include "game-engine/Entity/Entity.h"

#include <glm/glm.hpp>

class JointEntity : public Entity
{
private:
    
    glm::mat4 mLocalBindTransform;
    glm::mat4 mInverseBindTransform;

public:
    JointEntity(const std::string &name) : Entity(name, Entity::JOINT)
    {}

    void initialise() {}
    void update() {}
    
    //void setLocalBindPose(const glm::mat4 localBindPose) { this->mlocalBindPose = localBindPose;
    
        //this->transformOW(inverseBindPose);
    //}
    
    void setLocalBindTransform(const glm::mat4 localBindTransform) { this->mLocalBindTransform = localBindTransform; }

    void calculateInverseBindTransform();
    
    const glm::mat4& getLocalBindTransform() const { return this->mLocalBindTransform; }
    const glm::mat4& getInverseBindTransform() const { return this->mInverseBindTransform; }
    
private:
    
    void calculateInverseBindTransform(const glm::mat4 &parentBindTransform);
};

#endif /* _JOINTENTITY_H */
