#include "game-engine/Modules/Animation/Animation.h"

const JointAnimation* Animation::getJointAnimation(const std::string &name)
{
    if(mJointAnimations.find(name) != mJointAnimations.end())
    {
        return &mJointAnimations[name];
    }
    else
    {
        return NULL;
    }
}
