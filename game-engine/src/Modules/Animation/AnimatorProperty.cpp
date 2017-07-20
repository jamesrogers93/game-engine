
#include "game-engine/Modules/Animation/AnimatorProperty.h"

void AnimatorProperty::play(const std::string &animationKey)
{
    this->mAnimationKey = animationKey;
    this->mAnimate = true;
}

void AnimatorProperty::stop()
{
    this->mAnimate = false;
}

bool AnimatorProperty::animate()
{
    // Here we iterate over the joints and calculate their transforms
    
    return false;
}

bool AnimatorProperty::makeActive()
{
    this->mActive = true;
    
    AnimationModule *a = &AnimationModule::getInstance();
    
    return a->addAnimatorProperty(this->mName, this);
}

bool AnimatorProperty::makeUnactive()
{
    this->mActive = false;
    
    AnimationModule *a = &AnimationModule::getInstance();
    
    return a->removeAnimatorProperty(this->mName);
}
