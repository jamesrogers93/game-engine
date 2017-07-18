#include "game-engine/Modules/Animation/KeyFrame.h"

const JointTransform* KeyFrame::getJointTransform(const std::string &name)
{
    if(this->mJointTransforms.find(name) != this->mJointTransforms.end())
    {
        return &this->mJointTransforms[name];
    }
    else
    {
        return NULL;
    }
}

bool KeyFrame::addJointTransform(std::string &name, const JointTransform &jointTransform)
{
    if(this->mJointTransforms.find(name) == this->mJointTransforms.end())
    {
        this->mJointTransforms[name] = jointTransform;
        return true; 
    }
    else
    {
        return false;
    }
}
