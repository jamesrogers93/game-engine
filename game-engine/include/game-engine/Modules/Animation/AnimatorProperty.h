#ifndef _ANIMATORPROPERTY_H
#define _ANIMATORPROPERTY_H

// STD
#include <string>

#include "game-engine/Modules/Animation/AnimationModule.h"
#include "game-engine/Entity/Property.h"

class JointEntity;

class AnimatorProperty : public Property
{
    friend class AnimationModule;
public:
    AnimatorProperty(const std::string &name, JointEntity *skeletonRoot) : Property(name, Property::ANIMATOR), mSkeletonRoot(skeletonRoot), mAnimate(false)
    {}
    
    void play(const std::string &animationKey);
    void stop();
    bool animate();
    
    bool makeActive();
    bool makeUnactive();
    
private:

    JointEntity *mSkeletonRoot;
    bool mAnimate;
    std::string mAnimationKey;
};

#endif /* _ANIMATORPROPERTY_H */
