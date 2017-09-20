#ifndef _ANIMATORPROPERTY_H
#define _ANIMATORPROPERTY_H

// STD
#include <string>

#include "game-engine/Modules/Animation/AnimationModule.h"
#include "game-engine/Modules/Animation/Animation.h"
#include "game-engine/Modules/Animation/AnimationController.h"
#include "game-engine/Core/Main/Property.h"

class JointEntity;
class Animation;

class AnimatorProperty : public Property
{
    friend class AnimationModule;
public:
    
    AnimatorProperty(const std::string &name, JointEntity *skeletonRoot) : Property(name, Property::ANIMATOR), mSkeletonRoot(skeletonRoot)
    {}
    
    AnimationController* getAnimationController1() { return &mAnimationController1; }
    AnimationController* getAnimationController2() { return &mAnimationController2; }
    
    bool makeActive();
    bool makeUnactive();
    
private:

    JointEntity *mSkeletonRoot;
    
    AnimationController mAnimationController1;
    AnimationController mAnimationController2;
    
    void animate();
    
    void animate2(JointEntity *joint, std::vector<AnimationController*> &animationControllers, const glm::mat4 &parentTransform = glm::mat4());
    
    void updateFrame(const Animation* animation);
};

#endif /* _ANIMATORPROPERTY_H */
