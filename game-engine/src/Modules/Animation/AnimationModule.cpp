#include "game-engine/Modules/Animation/AnimationModule.h"

#include "game-engine/Util/StringUtil.h"

#include "game-engine/Modules/Animation/AnimatorProperty.h"
#include "game-engine/Modules/Animation/JointEntity.h"
#include "game-engine/Modules/Animation/Animation.h"
#include "game-engine/Modules/Animation/JointAnimation.h"
#include "game-engine/Modules/Animation/KeyFrame.h"
#include "game-engine/Modules/Animation/JointTransform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

bool AnimationModule::update()
{
    
    // Here we are going to update the animator properties.
    
    for(auto &animator : this->mAnimatorProperties)
    {
        if(!animator.second->mAnimate)
        {
            continue;
        }
        
        if(this->mAnimations.find(animator.second->mAnimationKey) != this->mAnimations.end())
        {
            Animation *a = this->mAnimations[animator.second->mAnimationKey];
            JointEntity *root = animator.second->mSkeletonRoot;
            
            animator.second->animate(a, root);
        }
    }
    
    
    return true;
}

bool AnimationModule::addAnimation(const std::string &name, Animation *animation)
{
    std::string nameLow = toLower(name);
    
    if(this->mAnimations.find(nameLow) == this->mAnimations.end())
    {
        this->mAnimations[nameLow] = animation;
        return true;
    }
    else
    {
        return false;
    }
}

bool AnimationModule::addAnimatorProperty(const std::string &name, AnimatorProperty *animtionProperty)
{
    std::string nameLow = toLower(name);
    
    if(this->mAnimatorProperties.find(nameLow) == this->mAnimatorProperties.end())
    {
        this->mAnimatorProperties[nameLow] = animtionProperty;
        return true;
    }
    else
    {
        return false;
    }
}

bool AnimationModule::removeAnimation(const std::string &name)
{
    std::string nameLow = toLower(name);
    
    std::map<std::string, Animation*>::iterator it = this->mAnimations.find(nameLow);
    if ( it != this->mAnimations.end())
    {
        this->mAnimations.erase(it);
        return true;
    }
    else
    {
        return false;
    }
}

bool AnimationModule::removeAnimatorProperty(const std::string &name)
{
    std::string nameLow = toLower(name);
    
    std::map<std::string, AnimatorProperty*>::iterator it = this->mAnimatorProperties.find(nameLow);
    if ( it != this->mAnimatorProperties.end())
    {
        this->mAnimatorProperties.erase(it);
        return true;
    }
    else
    {
        return false;
    }
}
