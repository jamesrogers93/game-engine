#ifndef _ANIMATION_H
#define _ANIMATION_H

// STD
#include <unordered_map>
#include <string>

#include "game-engine/Modules/Animation/JointAnimation.h"

class Animation
{
public:
    Animation(const std::string &name, const float &length, const std::unordered_map<std::string, JointAnimation> &jointAnimations) : mName(name), mLength(length), mJointAnimations(jointAnimations)
    {}
    
    const std::string& getName() const { return mName; }
    const float& getLength() const { return mLength; }
    const std::unordered_map<std::string, JointAnimation>* getJointAnimations() const { return &mJointAnimations; }
    const JointAnimation* getJointAnimation(const std::string &name) const;
    
private:
    std::string mName;
    float mLength;
    std::unordered_map<std::string, JointAnimation> mJointAnimations;
};

#endif /* _ANIMATION_H */
