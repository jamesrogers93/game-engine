#include "game-engine/Modules/Animation/JointAnimation.h"

const KeyFrame* JointAnimation::getKeyFrame(unsigned int &index) const
{
    if(index < this->mKeyFrames.size())
    {
        return &this->mKeyFrames[index];
    }
    else
    {
        return NULL;
    }
}

const KeyFrame* JointAnimation::getKeyFrame(const float &elapsedTime) const
{
    // If elapsed time is greater than the length of this animation, return the last keyframe
    if(elapsedTime > mLength)
    {
        return &mKeyFrames[mKeyFramesCount-1];
    }
    
    auto lower = std::lower_bound(mTimeStamps.begin(), mTimeStamps.end(), elapsedTime);
    
    if(lower != mTimeStamps.end())
    {
        auto idx = lower - mTimeStamps.begin();
        return &mKeyFrames[idx-1];
    }
    else
    {
        // Return the first keyframe
        return &mKeyFrames[0];
    }
}

void JointAnimation::setKeyFrames(const std::vector<KeyFrame> &keyFrames)
{
    mKeyFrames = keyFrames;
    
    mKeyFramesCount = keyFrames.size();
    
    for(unsigned int i = 0; i < mKeyFramesCount; i++)
    {
        mTimeStamps.push_back(keyFrames[i].getTimeStamp());
    }
}
