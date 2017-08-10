#ifndef _KEYFRAME_H
#define _KEYFRAME_H

#include "game-engine/Modules/Animation/JointTransform.h"

class KeyFrame
{
public:
    KeyFrame(const float &timeStamp, const JointTransform &jointTransform) : mTimeStamp(timeStamp), mJointTransform(jointTransform)
    {}
    
    const float& getTimeStamp() const { return mTimeStamp; }
    const JointTransform& getJointTransform() const { return mJointTransform; }
    
    //static const Joint interpolate(const float& progression, const KeyFrame* keyframe1, const KeyFrame* keyframe2)
    //{
        
    //    return KeyFrame
    //}
    
private:
    float mTimeStamp;
    JointTransform mJointTransform;
};

struct KeyFramePair
{
public:
    KeyFramePair(const KeyFrame* keyframe1, const KeyFrame* keyframe2, const bool &isPair, const float &progression) : mKeyframe1(keyframe1), mKeyframe2(keyframe2), mIsPair(isPair), mProgression(progression)
    {}
    
    const KeyFrame* mKeyframe1;
    const KeyFrame* mKeyframe2;
    
    const bool mIsPair;
    const float mProgression;
};

#endif /* _KEYFRAME_H */
