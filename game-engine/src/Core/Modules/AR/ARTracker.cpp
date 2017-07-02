#include "game-engine/Core/Modules/AR/ARTracker.h"

#include </Users/James/Documents/University/Advanced_Computer_Science/Year_1/Dissertation/Application/ar-fighter/ar-fighter-ios/ARFighter/KudanCV/KudanCV.h>


ARTracker::ARTracker()
{
}

void ARTracker::initalise()
{
    this->tracker = new KudanArbiTracker();
    
    KudanCameraParameters parameters;
    
    // Should use the camera to get the image stream size, but it's not initialised yet, so just hardcode for now
    parameters.setSize(1920, 1080);
    
    // Don't know the intrinsics so tell it to figure them out
    parameters.guessIntrinsics();
    
    // Important: set the intrinsic parameters on the tracker
    tracker->setCameraParameters(parameters);
    
    std::string key = "Y+TzM9lcb0EfiJxoEqEvLaOaAWMjtdvFiiO1av2Sjkxboj886KE1wJsruv3kJvVHKSWy6KUEQPeMrKAX5uuCQUuccbPErjQuYklwfpH0SdicLuUoEJvKy0KOGjlJO6sUtNgb+XOjJWRIfVB6TpfRKvXkEYcKE+iRA4CMJp5vj3BVkrrtNXjZh7obKUSEDZpPQKZi0KDsr6SQSoCzjTnwgW1+j4/71A260mYLWyMe4OF1uQU7wMyON1ToMpkFLJipkEe7S+4I68Cq9c7W6RArOJbUYjHPLfKrO7zpYpDt+vy8/xuc//nZKFlG4zJhiIoqjyvfrU5CeoSO7O2KZv/CfAJxqnRt/wBB+ju49VVacWUoFG8t/0MPRlaE8Yyjz+jgt6u0UQwB8AK3j+4qloEVCqav4PafjCnDcwBOGHNMFv72zcZyKgOGLFTNRVRXpTP02Z67Jh0POfZfRdV4Gl+jvT49rYzpzuEMkbfR2pqwIIu38HCYhLw6V3qeH/JqUif/n2IlPZglT35wDwDvtWBHWpzpW6ct/RzMjjf8Pfa79kPoBUCQpOPRFV9uDCfqYPVMN7/zRZtxauO+1wMgTJxzd4MjOF0wBYZcHRWw1WG9A/NT+FnhhZrHMjJgEVReVK08x1ubIkfqYJKPrD2/PmYNVBI0mGnGS9QO3v81Y0NDVrY=";
    
    tracker->setApiKey(key);
}
