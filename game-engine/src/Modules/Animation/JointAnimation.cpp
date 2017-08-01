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

const KeyFramePair JointAnimation::getKeyFramePair(const float &elapsedTime) const
{
    
    float time = elapsedTime;
    while(time > mLength)
    {
        time -= mLength;
    }
    
    auto lower = std::lower_bound(mTimeStamps.begin(), mTimeStamps.end(), time);
    
    if(lower != mTimeStamps.end())
    {
        auto idx = lower - mTimeStamps.begin();
        const KeyFrame* keyFrame1 = &mKeyFrames[idx-1];
        const KeyFrame* keyFrame2 = &mKeyFrames[idx];
        const bool isPair = true;
        
        float lowerBound = mTimeStamps[idx-1];
        float upperBound = mTimeStamps[idx] - lowerBound;
        float progression = elapsedTime - lowerBound;
        progression = progression / upperBound;
        
        KeyFramePair pair(keyFrame1, keyFrame2, isPair, progression);
        return pair;
    }
    else
    {
        // Return the first keyframe
        const KeyFrame* keyFrame1 = &mKeyFrames[0];
        const KeyFrame* keyFrame2 = &mKeyFrames[0];
        const bool isPair = false;
        
        KeyFramePair pair(keyFrame1, keyFrame2, isPair, 0.0);
        return pair;
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
