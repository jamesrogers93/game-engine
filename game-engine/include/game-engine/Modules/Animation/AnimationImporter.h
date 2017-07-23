#ifndef _ANIMATIONIMPORTER_H
#define _ANIMATIONIMPORTER_H

#include "game-engine/JMPImporter.h"

#include "game-engine/Modules/Animation/Animation.h"
#include "game-engine/Modules/Animation/JointAnimation.h"
#include "game-engine/Modules/Animation/KeyFrame.h"
#include "game-engine/Modules/Animation/JointTransform.h"

class Animation;

class AnimationImporter : public JMPImporter<Animation>
{
public:
    AnimationImporter() : JMPImporter()
    {}
    
    void ImportAsynchronously(const std::string &path);
    bool Import(const std::string &path);
    
private:
    Animation* importAnimation(const std::string &path, std::ifstream &file);
    JointAnimation importJointAnimation(std::ifstream &file);
    KeyFrame importKeyFrame(std::ifstream &file);
    JointTransform importJointTransform(std::ifstream &file);
};

#endif /* _ANIMATIONIMPORTER_H */
