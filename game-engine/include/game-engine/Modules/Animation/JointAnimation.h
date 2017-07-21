#ifndef _JOINTANIMATION_H
#define _JOINTANIMATION_H

// STD
#include <vector>

#include "game-engine/Modules/Animation/KeyFrame.h"
//#include "game-engine/Modules/Animation/JointAnimation.h"

class JointAnimation
{
public:
    
    JointAnimation()
    {}
    
    JointAnimation(const float &length, const std::vector<KeyFrame> &keyframes)
    : mLength(length), mKeyFrames(keyframes)
    {}
    
    const float& getLength() const { return this->mLength; }
    const std::vector<KeyFrame>& getKeyFrames() const { return this->mKeyFrames; }
    
    void setLength(const float &length) { mLength = length; }
    void setKeyFrames(const std::vector<KeyFrame> &keyFrames) { mKeyFrames = keyFrames; }
    
private:
    float mLength;
    std::vector<KeyFrame> mKeyFrames;
};

#endif /* _JOINTANIMATION_H */
