#include "game-engine/Modules/Animation/AnimatorProperty.h"
#include "game-engine/Modules/Animation/JointEntity.h"
#include "game-engine/Modules/Animation/Animation.h"
#include "game-engine/Modules/Animation/JointAnimation.h"
#include "game-engine/Modules/Animation/KeyFrame.h"
#include "game-engine/Modules/Animation/JointTransform.h"

#include "game-engine/Util/TimeUtil.h"

#include <iostream>

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

void AnimatorProperty::animate()
{
    //if(mAnimationController1.isPlaying())
    //{
        //mAnimationController1.updateElapsedTime(timeSinceLastUpdate);
        //animate2(mSkeletonRoot, mAnimationController1);
    //}
    
    std::vector<AnimationController*> animationControllers;
    
    if(mAnimationController1.isPlaying() && mAnimationController1.getAnimationPtr() != NULL)
    {
        mAnimationController1.updateElapsedTime(timeSinceLastUpdate);
        animationControllers.push_back(&mAnimationController1);
    }
    
    if(mAnimationController2.isPlaying() && mAnimationController2.getAnimationPtr() != NULL)
    {
        mAnimationController2.updateElapsedTime(timeSinceLastUpdate);
        animationControllers.push_back(&mAnimationController2);
    }
    
    
    if(animationControllers.size() > 0)
    {
        animate2(mSkeletonRoot, animationControllers);
    }
}

/*void AnimatorProperty::animate2(JointEntity *joint, const AnimationController &animationController, const glm::mat4 &parentTransform)
{
    
    // Get animation transform;
    const JointAnimation *jointAnimation = animationController.getAnimationPtr()->getJointAnimation(joint->getName());
    
    glm::mat4 jointLocalTransform;
    
    // Get the joint animation transformation
    if(jointAnimation != NULL)
    {
        KeyFramePair pair = jointAnimation->getKeyFramePair(animationController.getElapsedTime());
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
    
    for(unsigned int i = 0; i < joint->getChildren().size(); i++)
    {
        if(joint->getChildren()[i]->getType() == Entity::JOINT)
        {
            animate2((JointEntity*)joint->getChildren()[i], animationController, jointGlobalTransform);
        }
    }
}*/

void AnimatorProperty::animate2(JointEntity *joint, std::vector<AnimationController*> &animationControllers, const glm::mat4 &parentTransform)
{
    
    std::vector<JointTransform> jointTransforms;
    std::vector<float> blendAlphas;
    
    size_t numAnimationControllers = animationControllers.size();
    
    for(unsigned int i = 0; i < numAnimationControllers; i++)
    {
        
        const AnimationController *animationController = animationControllers[i];
        
        // Store the blend alpha of the animation
        blendAlphas.push_back(animationController->getAlpha());
        
        // Get animation transform;
        const JointAnimation *jointAnimation = animationController->getAnimationPtr()->getJointAnimation(joint->getName());
        
        // Get the joint animation transformation
        if(jointAnimation != NULL)
        {
            KeyFramePair pair = jointAnimation->getKeyFramePair(animationController->getAnimationTime());
            
            if(pair.mIsPair)
            {
                // Get the joint transforms from the keyframes
                const JointTransform *jointTransform1 = &pair.mKeyframe1->getJointTransform();
                const JointTransform *jointTransform2 = &pair.mKeyframe2->getJointTransform();
                
                // Interpolate the joint transforms
                JointTransform jointTransform = JointTransform::interpolate(pair.mProgression, jointTransform1, jointTransform2);
                
                // Store the jointTransform for blending later
                jointTransforms.push_back(jointTransform);
            }
            else
            {
                // Get the joint transforms from the keyframe
                const JointTransform *jointTransform = &pair.mKeyframe1->getJointTransform();
                
                // Store the jointTransform for blending later
                jointTransforms.push_back(*jointTransform);
            }
        }
        
        // If we dont have any jointTransforms, just use the localBind transform of the joint?
        // Keep this here just in case I'm wrong
        
        //else
        //{
            // Or get the local bind transform
        //    jointLocalTransform = joint->getLocalBindTransform();
        //}
    }
    
    
    // We have now finished finding all of the jointTransforms for the animation controllers
    
    // Three scenarios: (I think)
    // 1. No JointTransforms have been found - use the localBindTransform of the joint.
    // 2. One JointTransform has been found - use that as the localTransform without blending.
    // 3. More than one JointTransfom has been found - blend them using the blend alphas.
    
    glm::mat4 jointLocalTransform;
    size_t numJointTransforms = jointTransforms.size();
    
    // Scenario 1
    if(numJointTransforms == 0)
    {
        jointLocalTransform = joint->getLocalBindTransform();
    }
    
    // Scenario 2
    else if(numJointTransforms == 1)
    {
        glm::vec3 position = jointTransforms[0].getPosition();
        glm::fquat rotation = jointTransforms[0].getRotation();
        
        jointLocalTransform = glm::translate(glm::mat4(), glm::vec3(position)) * glm::mat4_cast(rotation);
    }
    
    // Scenario 3
    else
    {
        // Loop over JointTransforms
        for(unsigned int i = 1; i < numJointTransforms; i++)
        {
            // Get the two joint transforms
            JointTransform *jointTransformA = &jointTransforms[i-1];
            JointTransform *jointTransformB = &jointTransforms[i];
            
            // Get the two blend alphas
            float alphaA = blendAlphas[i-1];
            float alphaB = blendAlphas[i];
            
            // Normalise the blend alphas
            float sum = alphaA + alphaB;
            
            //float alphaAA = alphaA / sum;
            float alphaBB = alphaB / sum;
            
            
            // Interpolate the joint transforms
            JointTransform jointTransform = JointTransform::interpolate(alphaBB, jointTransformB, jointTransformA);
            
            // Add the new jointTransform to the current index
            // This is so that on the next iteration, we want to interpolate with this jointTransform
            jointTransforms[i] = jointTransform;
            blendAlphas[i] = sum;
            
            glm::vec3 position = jointTransform.getPosition();
            glm::fquat rotation = jointTransform.getRotation();
            
            jointLocalTransform = glm::translate(glm::mat4(), glm::vec3(position)) * glm::mat4_cast(rotation);
        }
    }
    
    
    glm::mat4 jointGlobalTransform = parentTransform * jointLocalTransform;
    joint->transformOW(jointGlobalTransform * joint->getInverseBindTransform());
    
    for(unsigned int i = 0; i < joint->getChildren().size(); i++)
    {
        if(joint->getChildren()[i]->getType() == Entity::JOINT)
        {
            animate2((JointEntity*)joint->getChildren()[i], animationControllers, jointGlobalTransform);
        }
    }
}


void AnimatorProperty::updateFrame(const Animation* animation)
{
    
}
