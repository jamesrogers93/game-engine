#ifndef _KEYFRAME_H
#define _KEYFRAME_H

// STD
#include <string>
#include <map>

#include "game-engine/Modules/Animation/JointTransform.h"

class KeyFrame
{
public:
    KeyFrame()
    {}
    
    KeyFrame(const std::map<std::string, JointTransform> &jointTransforms) : mJointTransforms(jointTransforms)
    {}
    
    const JointTransform* getJointTransform(const std::string&);
    bool addJointTransform(std::string&, const JointTransform&);
    
private:
    std::map<std::string, JointTransform> mJointTransforms;
};

#endif /* _KEYFRAME_H */
