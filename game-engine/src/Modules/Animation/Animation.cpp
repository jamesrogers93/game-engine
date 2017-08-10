#include "game-engine/Modules/Animation/Animation.h"

// STD
#include <iostream>

const JointAnimation* Animation::getJointAnimation(const std::string &name) const
{
    auto it = mJointAnimations.find(name);
    
    if(it != mJointAnimations.end())
    {
        return &it->second;
    }
    else
    {
    //    std::cout << "Joint Animation: " << name << " not found." << std::endl;
        return NULL;
    }
}
