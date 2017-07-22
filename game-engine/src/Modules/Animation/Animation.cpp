#include "game-engine/Modules/Animation/Animation.h"

const JointAnimation* Animation::getJointAnimation(const std::string &name) const
{
    if(mJointAnimations.find(name) != mJointAnimations.end())
    {
        return &mJointAnimations.at(name);
    }
    else
    {
        return NULL;
    }
}
