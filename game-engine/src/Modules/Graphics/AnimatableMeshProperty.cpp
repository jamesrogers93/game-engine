#include "game-engine/Modules/Graphics/AnimatableMeshProperty.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

// Game Engine
#include "game-engine/Modules/Graphics/Shader.h"
#include "game-engine/Entity/Entity.h"

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

void AnimatableMeshProperty::loadToShader(Shader *shader)
{
    // Load projection to shader
    GLint *loc =shader->getUniformLocation(SHADER_MODEL_NAME);
    if(loc != NULL)
    {
        glUniformMatrix4fv(*loc, 1, false, glm::value_ptr(this->mOwner->getGlobalModel()));
    }
    
    loc = shader->getUniformLocation(SHADER_NORMAL_MATRIX_NAME);
    if(loc != NULL)
    {
        glUniformMatrix3fv(*loc, 1, false, glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(this->mOwner->getGlobalModel())))));
    }
}

void AnimatableMeshProperty::fillUniformNames(std::vector<std::string> &uniformNames)
{
    uniformNames.push_back(SHADER_MODEL_NAME);
    uniformNames.push_back(SHADER_NORMAL_MATRIX_NAME);
}
