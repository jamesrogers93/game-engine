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
