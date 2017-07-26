#include "game-engine/Modules/Animation/AnimationImporter.h"

#include <iostream>
#include <fstream>

#include <glm/glm.hpp>

#include "game-engine/Modules/Animation/Animation.h"

#include "game-engine/Util/StringUtil.h"

void AnimationImporter::ImportAsynchronously(const std::string &path)
{
    mThread = std::thread(&AnimationImporter::Import, this, path);
}

bool AnimationImporter::Import(const std::string &path)
{
    
    std::ifstream file;
    file.open(path);
    if (!file)
    {
        std::cout << "Unable to open file " << path << std::endl;
        return false;
    }
    
    Animation *animation = importAnimation(path, file);
    
    this->importedObject = animation;
    
    file.close();
    
    return true;
}

Animation* AnimationImporter::importAnimation(const std::string &path, std::ifstream &file)
{
    // Get the name of the animation.
    // Here we take it from the file name
    std::string name = toLower(fileName(path, false));
    
    // Get length of the animation
    float length;
    file >> length;
    
    // Get number of joints in the animation
    unsigned int numJointAnimations;
    file >> numJointAnimations;
    
    // Get joint animations
    std::unordered_map<std::string, JointAnimation> jointAnimations;
    for(unsigned int i = 0; i < numJointAnimations; i++)
    {
        // Get joint animation name
        std::string jointAnimationName;
        file >> jointAnimationName;
        
        // Add it to the map
        jointAnimations[toLower(jointAnimationName)] = importJointAnimation(file);
    }
    
    return new Animation(name, length, jointAnimations);
    
}

JointAnimation AnimationImporter::importJointAnimation(std::ifstream &file)
{
    // Get number of key frames
    unsigned int numKeyFrames;
    file >> numKeyFrames;
    
    // Get length of the joint animation
    float length;
    file >> length;
    
    // Get the keyframes
    std::vector<KeyFrame> keyFrames;
    for(unsigned int i = 0; i < numKeyFrames; i++)
    {
        keyFrames.push_back(importKeyFrame(file));
    }
    
    return JointAnimation(length, keyFrames);
}

KeyFrame AnimationImporter::importKeyFrame(std::ifstream &file)
{
    // Get the timestamp of this keyframe
    float timeStamp;
    file >> timeStamp;
    
    // Get the joint transform
    JointTransform jointTransform = importJointTransform(file);
    
    return KeyFrame(timeStamp, jointTransform);
}

JointTransform AnimationImporter::importJointTransform(std::ifstream &file)
{
    // Get the position and rotation of the joint transform
    glm::vec4 position;
    glm::fquat rotation;
    
    file >> position.x >> position.y >> position.z >> position.w;
    file >> rotation.x >> rotation.y >> rotation.z >> rotation.w;
    
    return JointTransform(position, rotation);
}
