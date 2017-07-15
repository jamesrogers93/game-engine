#include "game-engine/Animatable.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

// Game Engine
#include "game-engine/Modules/Graphics/Shader.h"

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

const std::string AnimatableEntity::SHADER_MODEL_NAME = "model";
const std::string AnimatableEntity::SHADER_NORMAL_MATRIX_NAME = "normal_matrix";

AnimatableEntity::AnimatableEntity(const std::string &name) : Entity(name)
{
    
}

void AnimatableEntity::loadToShader(Shader *shader)
{
    // Load projection to shader
    GLint *loc =shader->getUniformLocation(SHADER_MODEL_NAME);
    if(loc != NULL)
    {
        glUniformMatrix4fv(*loc, 1, false, glm::value_ptr(this->globalModel));
    }
    
    loc = shader->getUniformLocation(SHADER_NORMAL_MATRIX_NAME);
    if(loc != NULL)
    {
        glUniformMatrix3fv(*loc, 1, false, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(this->globalModel)))));
    }
}

void AnimatableEntity::fillUniformNames(std::vector<std::string> &uniformNames)
{
    uniformNames.push_back(SHADER_MODEL_NAME);
    uniformNames.push_back(SHADER_NORMAL_MATRIX_NAME);
}
