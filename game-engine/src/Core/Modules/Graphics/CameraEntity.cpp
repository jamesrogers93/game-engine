#include "game-engine/Core/Modules/Graphics/CameraEntity.h"

// GLM
#include <glm/gtc/matrix_transform.hpp>

const glm::vec3 CameraEntity::DEFAULT_UP = glm::vec3(0.0, 1.0, 0.0);
const glm::vec3 CameraEntity::DEFAULT_WORLDUP = glm::vec3(0.0, 1.0, 0.0);
const float CameraEntity::DEFAULT_YAW = 0.0f;
const float CameraEntity::DEFAULT_PITCH = 0.0f;

void CameraEntity::update()
{
    // Calculate the front, right and up vector
    glm::vec3 front;
    front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    front.y = sin(glm::radians(this->pitch));
    front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    
    this->front = glm::normalize(front);
    glm::vec3 right = glm::normalize(glm::cross(this->front, DEFAULT_WORLDUP));
    this->up = glm::normalize(glm::cross(right, this->front));
    
    // Calculate the view matrix
    this->view = glm::lookAt(this->position, this->position + this->front, this->up);
}

const glm::mat4& CameraEntity::getView()
{
    return this->view;
}
