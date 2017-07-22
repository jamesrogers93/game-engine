#ifndef _ANIMATORPROPERTY_H
#define _ANIMATORPROPERTY_H

// STD
#include <string>

#include "game-engine/Modules/Animation/AnimationModule.h"
#include "game-engine/Entity/Property.h"

class JointEntity;
class Animation;

class AnimatorProperty : public Property
{
    friend class AnimationModule;
public:
    AnimatorProperty(const std::string &name, JointEntity *skeletonRoot) : Property(name, Property::ANIMATOR), mSkeletonRoot(skeletonRoot), mAnimate(false)
    {}
    
    void play(const std::string &animationKey, const bool &loop = false, const float &speed = 1.0, const bool &reverse = false);
    void stop();
    
    bool makeActive();
    bool makeUnactive();
    
    const float& getStartTime() { return mStartTime; }
    const bool& getLoop() { return mLoop; }
    const bool& getReverse() { return mReverse; }
    const float& getSpeed() { return mSpeed; }
    
private:

    JointEntity *mSkeletonRoot;
    std::string mAnimationKey;
    
    bool mAnimate;
    float mStartTime;
    bool mLoop;
    bool mReverse;
    float mSpeed;
    
    void animate(const Animation *animation, JointEntity *joint);
    
    void animate2(const Animation *animation, JointEntity *joint, const float &elapsedTime, const glm::mat4 &parentTransform = glm::mat4());
    
    void updateFrame(const Animation* animation);
};

#endif /* _ANIMATORPROPERTY_H */
