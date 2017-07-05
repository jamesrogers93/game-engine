#include "game-engine/Core/Modules/Graphics/CameraEntity.h"
#include "game-engine/Core/Modules/Graphics/Shader.h"
#include "game-engine/Core/Modules/Graphics/Graphics.h"

// GLM
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

const std::string CameraEntity::SHADER_PROJECTION_NAME = "camera_projection";
const std::string CameraEntity::SHADER_VIEW_NAME = "camera_view";
const std::string CameraEntity::SHADER_POSITION_NAME = "camera_position";

const glm::vec3 CameraEntity::DEFAULT_UP = glm::vec3(0.0, 1.0, 0.0);
const glm::vec3 CameraEntity::DEFAULT_WORLDUP = glm::vec3(0.0, 1.0, 0.0);
const glm::vec3 CameraEntity::DEFAULT_FRONT = glm::vec3(0.0, 0.0, 1.0);
const float CameraEntity::DEFAULT_FOV = 75.0f;
const float CameraEntity::DEFAULT_CLIPNEAR = 1.0f;
const float CameraEntity::DEFAULT_CLIPFAR = 1000.0f;

CameraEntity::CameraEntity(const std::string &name, const glm::mat4& projection, const glm::vec3 &position, const glm::vec3 &front) : ENode(name, position), projection(projection), front(front)
{
    glm::vec3 right = glm::normalize(glm::cross(this->front, DEFAULT_WORLDUP));
    this->up = glm::normalize(glm::cross(right, this->front));
    this->updateView();
}

CameraEntity::CameraEntity(const std::string &name, const glm::mat4& projection, const float &posX, const float &posY, const float &posZ, const glm::vec3 &front) : ENode(name, glm::vec3(posX, posY, posZ)), projection(projection), front(front)
{
    glm::vec3 right = glm::normalize(glm::cross(this->front, DEFAULT_WORLDUP));
    this->up = glm::normalize(glm::cross(right, this->front));
    this->updateView();
}

void CameraEntity::update()
{
    updateView();
}

void CameraEntity::updateView()
{
    // TEST
    //this->view = glm::translate(glm::mat4(), glm::vec3(0.0, 0.0, -10.0));
    this->view = glm::inverse(this->globalModel);
    //END TEST
    
    // CURRENT
    /*glm::vec3 globalPosition = glm::vec3(this->globalModel[3]);
    glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(this->globalModel)));
    glm::vec3 globalFront = this->front * normalMatrix;
    glm::vec3 globalUp = this->up * normalMatrix;
    this->view = glm::lookAt(globalPosition, globalPosition + globalFront, globalUp);*/
    // END CURRENT
    
    //this->view = this->T * this->R;
    
    /*glm::mat4 transformation = this->globalModel; // your transformation matrix.
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(transformation, scale, rotation, translation, skew, perspective);
    
    this->view = glm::translate(glm::mat4(), translation) * glm::mat4_cast(rotation);*/
}

const glm::mat4& CameraEntity::getView()
{
    return this->view;
}

void CameraEntity::loadToShader(Shader *shader)
{
    // Load projection to shader
    GLint loc = *shader->getUniformLocation(SHADER_PROJECTION_NAME);
    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(this->projection));
    
    // load view to shader
    loc = *shader->getUniformLocation(SHADER_VIEW_NAME);
    glUniformMatrix4fv(loc, 1, false, glm::value_ptr(this->view));
    
    loc = *shader->getUniformLocation(SHADER_POSITION_NAME);
    glUniform3fv(loc, 1, glm::value_ptr(this->position));
}

glm::mat4 CameraEntity::perspectiveMatrix(const unsigned int &screenWidth, const unsigned int &screenHeight, const float &fov, const float &clipNear, const float &clipFar)
{
    return glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, clipNear, clipFar);
}

void CameraEntity::initialise()
{
    Graphics *g = &Graphics::getInstance();
    
    g->addCameraEntity(this->name, this);
}

void CameraEntity::fillUniformNames(std::vector<std::string> &uniformNames)
{
    uniformNames.push_back(SHADER_PROJECTION_NAME);
    uniformNames.push_back(SHADER_VIEW_NAME);
    uniformNames.push_back(SHADER_POSITION_NAME);
}
