#include "game-engine/Modules/Animation/JointEntity.h"



void JointEntity::calculateInverseBindTransform()
{
    calculateInverseBindTransform(glm::mat4());
}

void JointEntity::calculateInverseBindTransform(const glm::mat4 &parentBindTransform)
{
    glm::mat4 bindTransform = parentBindTransform * this->mLocalBindTransform;
    
    this->mInverseBindTransform = glm::inverse(bindTransform);
    
    size_t numChildren = this->children.size();
    for(unsigned int i = 0; i < numChildren; i++)
    {
        if(this->children[i]->getType() == Entity::JOINT)
        {
            JointEntity *joint = (JointEntity*)this->children[i];
            joint->calculateInverseBindTransform(bindTransform);
        }
    }
}
