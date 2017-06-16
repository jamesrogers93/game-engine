#ifndef _CAMERAENTITY_H
#define _CAMERAENTITY_H

// Game Engine Core
#include "game-engine/Core/Entity/ENode.h"

// GLM
#include <glm/glm.hpp>

class Shader;

class CameraEntity : public ENode
{
public:
    CameraEntity(const std::string &name, const glm::mat4& projection, const glm::vec3 &position, const glm::vec3 &front = DEFAULT_FRONT);
    
    CameraEntity(const std::string &name, const glm::mat4& projection, const float &posX, const float &posY, const float &posZ, const glm::vec3 &front = DEFAULT_FRONT);
    
    void updateView();
    const glm::mat4& getView();
    void loadToShader(Shader *shader);
    
    static glm::mat4 perspectiveMatrix(const unsigned int &screenWidth, const unsigned int &screenHeight, const float &fov = DEFAULT_FOV, const float &clipNear = DEFAULT_CLIPNEAR, const float &clipMFAR = DEFAULT_CLIPFAR);
    
private:
    
    static const glm::vec3 DEFAULT_UP;
    static const glm::vec3 DEFAULT_FRONT;
    static const glm::vec3 DEFAULT_WORLDUP;
    static const float DEFAULT_FOV;
    static const float DEFAULT_CLIPNEAR;
    static const float DEFAULT_CLIPFAR;
    
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    
    //float yaw;
    //float pitch;
    
    void attachToEngine();
};

#endif /* _CAMERAENTITY_H */
