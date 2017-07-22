#include "game-engine/Modules/Graphics/MeshProperty.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

#include "game-engine/Entity/Entity.h"

// Game Engine Core
#include "game-engine/Modules/Graphics/Graphics.h"
#include "game-engine/Modules/Graphics/Shader.h"

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

const std::string MeshProperty::SHADER_MODEL_NAME = "model";
const std::string MeshProperty::SHADER_NORMAL_MATRIX_NAME = "normal_matrix";

/*void MeshProperty::initialise()
{
    Graphics *g = &Graphics::getInstance();
    
    g->addMeshProperty(this->mName, this);
}*/

bool MeshProperty::makeActive()
{
    Property::makeActive();
    
    Graphics *g = &Graphics::getInstance();
    
    return g->addMeshProperty(this->mName, this);
}

bool MeshProperty::makeUnactive()
{
    Property::makeUnactive();
    
    Graphics *g = &Graphics::getInstance();
    
    return g->removeMeshProperty(this->mName);
}

void MeshProperty::loadToShader(Shader *shader)
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

void MeshProperty::fillUniformNames(std::vector<std::string> &uniformNames)
{
    uniformNames.push_back(SHADER_MODEL_NAME);
    uniformNames.push_back(SHADER_NORMAL_MATRIX_NAME);
}