#ifndef _CAMERAENTITY_H
#define _CAMERAENTITY_H

// STD
#include <string>


// Game Engine Core
#include "game-engine/Core/GL/GLData.h"

// Game Engine Graphics
#include "game-engine/Core/Main/Entity.h"
#include "game-engine/Modules/Graphics/Shader.h"

// GLM
#include <glm/glm.hpp>

class Shader;

class CameraEntity : public Entity
{
private:
    static const std::string SHADER_PROJECTION_NAME;
    static const std::string SHADER_VIEW_NAME;
    static const std::string SHADER_POSITION_NAME;
    
    static const glm::vec3 DEFAULT_UP;
    static const glm::vec3 DEFAULT_FRONT;
    static const glm::vec3 DEFAULT_WORLDUP;
    static const float DEFAULT_FOV;
    static const float DEFAULT_CLIPNEAR;
    static const float DEFAULT_CLIPFAR;
    
public:
    CameraEntity(const std::string &name, const glm::mat4& projection, const glm::vec3 &front = DEFAULT_FRONT);
    ~CameraEntity();
    
    void initialise();
    void deinitialise();
    void update();
    void updateView();
    
    const glm::mat4& getView();
    void loadToShader(Shader *shader);
    
    static void fillUniformNames(std::vector<std::string> &uniformNames);
    
    static glm::mat4 perspectiveMatrix(const unsigned int &screenWidth, const unsigned int &screenHeight, const float &fov = DEFAULT_FOV, const float &clipNear = DEFAULT_CLIPNEAR, const float &clipMFAR = DEFAULT_CLIPFAR);
    
private:
    
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 front;
    glm::vec3 up;
    
    //float yaw;
    //float pitch;
    
    UpdateNotification mViewGLUpdate;
    UpdateNotification mProjectionGLUpdate;
    
};

#endif /* _CAMERAENTITY_H */
