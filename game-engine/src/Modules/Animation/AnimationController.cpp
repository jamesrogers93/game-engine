#include "game-engine/Modules/Animation/AnimationController.h"
#include "game-engine/Modules/Animation/AnimationModule.h"
#include "game-engine/Modules/Animation/Animation.h"

void AnimationController::updateElapsedTime(const double &elapsedTime)
{
    mElapsedTime += (elapsedTime * mSpeed);
    mAnimationTime = mElapsedTime;
    
    // Check if elapsed time has passed animation length
    if(mAnimationTime > mAnimationPtr->getLength())
    {
        // If animation is looping, reset animation timings
        if(mLoop)
        {
            mElapsedTime = 0.0;
            mAnimationTime -= mAnimationPtr->getLength();
        }
        else
        {
            //mCallback();
            try {
                mCallback();
            } catch(const std::bad_function_call& e) {
                // Ignore
            }
            stop();
            return;
        }
    }
    
    // Reverse animation
    if(mReverse)
    {
        mAnimationTime = mAnimationPtr->getLength() - mAnimationTime;
    }
}

void AnimationController::setAnimation(const std::string &animation)
{
    AnimationModule *a = &AnimationModule::getInstance();
    
    mAnimationPtr = a->getAnimation(animation);
    mAnimationKey = animation;
}
