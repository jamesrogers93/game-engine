#ifndef _JOINTANIMATION_H
#define _JOINTANIMATION_H

// STD
#include <vector>
#include <utility>

#include "game-engine/Modules/Animation/KeyFrame.h"
//#include "game-engine/Modules/Animation/JointAnimation.h"

class JointAnimation
{
public:
    
    JointAnimation()
    {}
    
    JointAnimation(const float &length, const std::vector<KeyFrame> &keyFrames)
    : mLength(length)
    {
        setKeyFrames(keyFrames);
    }
    
    const float& getLength() const { return this->mLength; }
    const std::vector<KeyFrame>* getKeyFrames() const { return &this->mKeyFrames; }
    const KeyFrame* getKeyFrame(unsigned int &index) const;
    const size_t& getKeyFrameCount() const { return mKeyFramesCount; }
    
    void setLength(const float &length) { mLength = length; }
    void setKeyFrames(const std::vector<KeyFrame> &keyFrames);
    
    const KeyFramePair getKeyFramePair(const float &elapsedTime) const;
    const KeyFrame* getKeyFrame(const float &elapsedTime) const;
    
private:
    float mLength;
    std::vector<KeyFrame> mKeyFrames;
    std::vector<float> mTimeStamps;
    size_t mKeyFramesCount;
};

#endif /* _JOINTANIMATION_H */
