#include "game-engine/Modules/Animation/AnimatorProperty.h"
#include "game-engine/Modules/Animation/JointEntity.h"
#include "game-engine/Modules/Animation/Animation.h"
#include "game-engine/Modules/Animation/JointAnimation.h"
#include "game-engine/Modules/Animation/KeyFrame.h"
#include "game-engine/Modules/Animation/JointTransform.h"

#include "game-engine/Util/TimeUtil.h"

#include <iostream>

void AnimatorProperty::play(const std::string &animationKey, const bool &loop, const float &speed, const bool &reverse)
{
    AnimationModule *a = &AnimationModule::getInstance();
    
    animationPtr = a->getAnimation(animationKey);
    
    this->mAnimationKey = animationKey;
    this->mAnimate = true;
    this->mLoop = loop;
    this->mReverse = reverse;
    this->mSpeed = speed;
    this->mElapsedTime = 0.0; //this->mStartTime = timeInSeconds();
}

void AnimatorProperty::stop()
{
    this->mAnimate = false;
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

void AnimatorProperty::animate(const Animation *animation, JointEntity *joint)
{
    // Get Elapsed time
    
    //float currentTime = timeInSeconds();
    //float elapsedTime = currentTime - mStartTime;
    mElapsedTime += timeSinceLastUpdate;
    float elapsedTime = mElapsedTime;
    
    // Apply speed
    elapsedTime *= mSpeed;
    
    // Check if elapsed time has passed animation length
    if(elapsedTime > animation->getLength())
    {
        // If animation is looping, reset animation timings
        if(mLoop)
        {
            //mStartTime = currentTime;
            //elapsedTime -= animation->getLength();
            mElapsedTime = 0.0;
            elapsedTime -= animation->getLength();
        }
        else
        {
            stop();
            return;
        }
    }
    
    // Reverse animation
    if(mReverse)
    {
        elapsedTime = animation->getLength() - elapsedTime;
    }
    
    //std::cout << "elapsed time:" << elapsedTime << std::endl;
    
    animate2(animation, joint, elapsedTime);
}

void AnimatorProperty::animate2(const Animation *animation, JointEntity *joint, const float &elapsedTime, const glm::mat4 &parentTransform)
{
    
    // Get animation transform;
    const JointAnimation *jointAnimation = animation->getJointAnimation(joint->getName());
    
    glm::mat4 jointLocalTransform;
    
    // Get the joint animation transformation
    if(jointAnimation != NULL)
    {
        /*const JointTransform *jointTransform = &jointAnimation->getKeyFrame(elapsedTime)->getJointTransform();
        const glm::vec4 *position = &jointTransform->getPosition();
        const glm::fquat *rotation = &jointTransform->getRotation();*/
        
        KeyFramePair pair = jointAnimation->getKeyFramePair(elapsedTime);
        glm::vec4 position;
        glm::fquat rotation;
        
        if(pair.mIsPair)
        {
            const JointTransform *jointTransform1 = &pair.mKeyframe1->getJointTransform();
            const JointTransform *jointTransform2 = &pair.mKeyframe2->getJointTransform();
            
            JointTransform jointTransform = JointTransform::interpolate(pair.mProgression, jointTransform1, jointTransform2);
            
            position = jointTransform.getPosition();
            rotation = jointTransform.getRotation();
        }
        else
        {
            const JointTransform *jointTransform = &pair.mKeyframe1->getJointTransform();
            position = jointTransform->getPosition();
            rotation = jointTransform->getRotation();
        }
        
        
        jointLocalTransform = glm::translate(glm::mat4(), glm::vec3(position)) * glm::mat4_cast(rotation);
    }
    else
    {
        // Or get the local bind transform
        jointLocalTransform = joint->getLocalBindTransform();
    }
    
    glm::mat4 jointGlobalTransform = parentTransform * jointLocalTransform;
    joint->transformOW(jointGlobalTransform * joint->getInverseBindTransform());
    //joint->transformOW(joint->getInverseBindTransform());
    
    for(unsigned int i = 0; i < joint->getChildren().size(); i++)
    {
        if(joint->getChildren()[i]->getType() == Entity::JOINT)
        {
            animate2(animation, (JointEntity*)joint->getChildren()[i], elapsedTime, jointGlobalTransform);
        }
    }
}

void AnimatorProperty::updateFrame(const Animation* animation)
{
    
}
