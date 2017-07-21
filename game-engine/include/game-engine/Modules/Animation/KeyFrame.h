#ifndef _KEYFRAME_H
#define _KEYFRAME_H

// STD
#include <string>
#include <map>

#include "game-engine/Modules/Animation/JointTransform.h"

class KeyFrame
{
public:
    KeyFrame(const float &timeStamp, const JointTransform &jointTransform) : mTimeStamp(timeStamp), mJointTransform(jointTransform)
    {}
    
    const float& getTimeStamp() const { return mTimeStamp; }
    const JointTransform& getJointTransform() const { return mJointTransform; }
    
private:
    float mTimeStamp;
    JointTransform mJointTransform;
};

#endif /* _KEYFRAME_H */
