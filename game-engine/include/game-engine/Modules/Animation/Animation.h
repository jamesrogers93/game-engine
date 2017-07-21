#ifndef _ANIMATION_H
#define _ANIMATION_H

// STD
#include <map>
#include <string>

#include "game-engine/Modules/Animation/JointAnimation.h"

class Animation
{
public:
    Animation(const float &length, const std::map<std::string, JointAnimation> &jointAnimations) : mLength(length), mJointAnimations(jointAnimations)
    {}
    
    const float& getLength() const { return mLength; }
    const std::map<std::string, JointAnimation>& getJointAnimations() const { return mJointAnimations; }
    
private:
    float mLength;
    std::map<std::string, JointAnimation> mJointAnimations;
};

#endif /* _ANIMATION_H */
