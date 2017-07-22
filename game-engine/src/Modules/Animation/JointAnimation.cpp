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
    
    // Return the greatest keyframe that is less than elasped time
    for(unsigned int i = 0; i < mKeyFramesCount; i++)
    {
        if(mKeyFrames[i].getTimeStamp() > elapsedTime)
        {
            return &mKeyFrames[i-1];
        }
    }
    
    // Return thes first keyframe
    return &mKeyFrames[0];
}
