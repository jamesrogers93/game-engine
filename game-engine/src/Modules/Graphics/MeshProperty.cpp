#include "game-engine/Modules/Graphics/MeshProperty.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

// Game Engine Core
#include "game-engine/Modules/Graphics/Graphics.h"
#include "game-engine/Modules/Graphics/Shader.h"

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

const std::string MeshProperty::SHADER_MODEL_NAME = "model";
const std::string MeshProperty::SHADER_NORMAL_MATRIX_NAME = "normal_matrix";

MeshProperty::MeshProperty(const std::string &name, const std::string &geometryKey, const std::string &materialKey, const std::string &shaderKey)
: Entity(name)
{

    // Make geometry key lower case
    std::string gLow = geometryKey;
    std::transform(gLow.begin(), gLow.end(), gLow.begin(), ::tolower);
    this->geometry = gLow;
    
    // Make material key lower case
    std::string mLow = materialKey;
    std::transform(mLow.begin(), mLow.end(), mLow.begin(), ::tolower);
    this->material = mLow;
    
    // Make shader key lower case
    std::string sLow = shaderKey;
    std::transform(sLow.begin(), sLow.end(), sLow.begin(), ::tolower);
    this->shader = sLow;
}

void MeshProperty::initialise()
{
    Graphics *g = &Graphics::getInstance();
    
    g->addMeshProperty(this->name, this);
}

void MeshProperty::loadToShader(Shader *shader)
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

void MeshProperty::fillUniformNames(std::vector<std::string> &uniformNames)
{
    uniformNames.push_back(SHADER_MODEL_NAME);
    uniformNames.push_back(SHADER_NORMAL_MATRIX_NAME);
}
