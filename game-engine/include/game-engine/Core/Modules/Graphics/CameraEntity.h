#ifndef _CAMERAENTITY_H
#define _CAMERAENTITY_H

// Game Engine Core
#include "game-engine/Core/Entity/ENode.h"

// GLM
#include <glm/glm.hpp>

class CameraEntity : public ENode
{
public:
    CameraEntity(const std::string &name, const glm::vec3 &position, const glm::vec3 &up = DEFAULT_UP, const float &yaw = DEFAULT_YAW, const float &pitch = DEFAULT_PITCH)
    : ENode(name, position), up(up), yaw(yaw), pitch(pitch)
    {
        this->update();
    }
    
    void update();
    
    const glm::mat4& getView();
    
private:
    
    static const glm::vec3 DEFAULT_UP;
    static const glm::vec3 DEFAULT_WORLDUP;
    static const float DEFAULT_YAW;
    static const float DEFAULT_PITCH;
    
    glm::vec3 front;
    glm::vec3 up;
    glm::mat4 view;
    
    float yaw;
    float pitch;
};

#endif /* _CAMERAENTITY_H */
