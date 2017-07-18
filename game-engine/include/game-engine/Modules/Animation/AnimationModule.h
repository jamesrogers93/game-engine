#ifndef _ANIMATIONMODULE_H
#define _ANIMATIONMODULE_H

// STD
#include <string>
#include <map>

#include "game-engine/Modules/CoreModule.h"

class Animation;
class AnimatorProperty;

class AnimationModule : public CoreModule
{
public:
    
    static AnimationModule& getInstance()
    {
        static AnimationModule    instance;
        return instance;
    }
    
    bool initalise() {}
    bool deinitalise() {}
    bool update() {}
    
private:
    AnimationModule() : CoreModule(CM_ANIMATION){}
    AnimationModule(AnimationModule const&);    // Don't Implement
    void operator=(AnimationModule const&);		// Don't implement
    
    std::map<std::string, Animation*> animations;
    std::map<std::string, AnimatorProperty> animatorProperties;
};

#endif /* _ANIMATIONMODULE_H */
