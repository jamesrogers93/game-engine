#ifndef _ANIMATIONMODULE_H
#define _ANIMATIONMODULE_H

// STD
#include <string>
#include <map>

#include "game-engine/Modules/CoreModule.h"

#include <glm/glm.hpp>

class Animation;
class AnimatorProperty;
class JointEntity;

class AnimationModule : public CoreModule
{
public:
    
    static AnimationModule& getInstance()
    {
        static AnimationModule    instance;
        return instance;
    }
    
    bool initalise() { return true; }
    bool deinitalise() { return true; }
    bool update();
    
    bool addAnimation(const std::string&, Animation*);
    bool addAnimatorProperty(const std::string&, AnimatorProperty*);
    
    bool removeAnimation(const std::string&);
    bool removeAnimatorProperty(const std::string&);
    
private:
    AnimationModule() : CoreModule(CM_ANIMATION){}
    AnimationModule(AnimationModule const&);    // Don't Implement
    void operator=(AnimationModule const&);		// Don't implement
    
    std::map<std::string, Animation*> mAnimations;
    std::map<std::string, AnimatorProperty*> mAnimatorProperties;
    
    void animate(Animation *animation, JointEntity *joint, const glm::mat4 &parentTransform);
};

#endif /* _ANIMATIONMODULE_H */
