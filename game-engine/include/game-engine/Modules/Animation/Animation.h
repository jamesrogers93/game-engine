#ifndef _ANIMATION_H
#define _ANIMATION_H

// STD
#include <vector>

#include "game-engine/Modules/Animation/KeyFrame.h"

class Animation
{
public:
    Animation(const float &length, const float &ticksPerSecond, const std::vector<KeyFrame> &keyframes)
    : mLength(length), mTicksPerSecond(ticksPerSecond), mKeyframes(keyframes)
    {}
    
    const length& getLength() const;
    const float& getTicksPerSecond() const;
    const std::vector<KeyFrame>& getKeyFrames() const;
    
private:
    float mLength;
    float mTicksPerSecond;
    std:vector<KeyFrame> mKeyframes;
};

#endif /* _ANIMATION_H */
