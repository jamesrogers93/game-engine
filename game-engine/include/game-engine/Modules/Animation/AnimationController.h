
#ifndef _ANIMATIONCONTROLLER_H
#define _ANIMATIONCONTROLLER_H

#include <string>
#include <functional>

class Animation;

class AnimationController
{
private:
    std::string mAnimationKey;
    const Animation* mAnimationPtr;
    bool mLoop;
    bool mReverse;
    float mSpeed;
    float mAlpha;
    double mElapsedTime;
    double mAnimationTime;
    bool mPlay;
    std::function<void()> mCallback;
    
public:
    AnimationController() : mAnimationKey(""), mAnimationPtr(NULL), mLoop(false), mReverse(false), mSpeed(1.0), mAlpha(1.0), mElapsedTime(0.0), mPlay(false)
    {}
    
    void play() { mPlay = true; }
    void stop() { mPlay = false; }
    
    const std::string& getmAnimationKey() const { return mAnimationKey; }
    const Animation* getAnimationPtr() const { return mAnimationPtr; }
    const bool& getLoop() const { return mLoop; }
    const bool& getReverse() const { return mReverse; }
    const float& getSpeed() const { return mSpeed; }
    const float& getAlpha() const { return mAlpha; }
    //const double& getElapsedTime() const { return mElapsedTime; }
    const double& getAnimationTime() const { return mAnimationTime; }
    const bool& isPlaying() { return mPlay; }
    
    void setAnimation(const std::string &animation);
    
    void setLoop(const bool &loop) { mLoop = loop; }
    void setReverse(const bool &reverse) { mReverse = reverse; }
    void setSpeed(const float &speed) { mSpeed = speed; }
    void setAlpha(const float &alpha) { mAlpha = alpha; }
    void setCallback(std::function<void()> callback) { mCallback = callback; }
    
    void updateElapsedTime(const double &elapsedTime);
    
    void resetElapsedTime() { mElapsedTime = 0.0; }
    
    
};

#endif /* _ANIMATIONCONTROLLER_H */
