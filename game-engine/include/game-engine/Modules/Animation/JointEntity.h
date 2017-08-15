#ifndef _JOINTENTITY_H
#define _JOINTENTITY_H

#include "game-engine/Entity/Entity.h"

#include <glm/glm.hpp>

class JointEntity : public Entity
{
private:
    
    glm::mat4 mLocalBindTransform;
    glm::mat4 mInverseBindTransform;
    glm::mat4 mLocalJointModel; // This is different to the entity local model as it contains the inverse bind pose to transform the mesh to the origin.

public:
    JointEntity(const std::string &name) : Entity(name, Entity::JOINT)
    {}

    void initialise() {}
    void deinitialise() {}
    //void update() { }//this->localModel = this->mInverseBindTransform; }
    
    void setLocalBindTransform(const glm::mat4 localBindTransform) { this->mLocalBindTransform = localBindTransform; transformOW(localBindTransform); }
    void setInverseBindTransform(const glm::mat4 inverseBindTransform) { this->mInverseBindTransform = inverseBindTransform; }
    
    void transformLocalJointModel(const glm::mat4 &M) { mLocalJointModel = M; }

    void calculateInverseBindTransform();
    
    const glm::mat4& getLocalBindTransform() const { return this->mLocalBindTransform; }
    const glm::mat4& getInverseBindTransform() const { return this->mInverseBindTransform; }
    const glm::mat4& getLocalJointModel() const { return this->mLocalJointModel; }
    
private:
    
    void calculateInverseBindTransform(const glm::mat4 &parentBindTransform);
};

#endif /* _JOINTENTITY_H */
