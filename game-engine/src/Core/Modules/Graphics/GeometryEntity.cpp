#include "game-engine/Core/Modules/Graphics/GeometryEntity.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

// Game Engine Core
#include "game-engine/Core/Modules/Graphics/Graphics.h"
#include "game-engine/Core/Modules/Graphics/Shader.h"

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

const std::string GeometryEntity::SHADER_MODEL_NAME = "model";
const std::string GeometryEntity::SHADER_NORMAL_MATRIX_NAME = "normal_matrix";

GeometryEntity::GeometryEntity(const std::string &name, const glm::vec3 &position, const std::string &geometryKey, const std::string &materialKey, const std::string &shaderKey)
: ENode(name, position)
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

GeometryEntity::GeometryEntity(const std::string &name, const float &posX, const float &posY, const float &posZ, const std::string &geometryKey, const std::string &materialKey, const std::string &shaderKey)
: ENode(name, glm::vec3(posX, posY, posZ))
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

void GeometryEntity::initialise()
{
    Graphics *g = &Graphics::getInstance();
    
    g->addGeometryEntity(this->name, this);
}

void GeometryEntity::loadToShader(Shader *shader)
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

void GeometryEntity::fillUniformNames(std::vector<std::string> &uniformNames)
{
    uniformNames.push_back(SHADER_MODEL_NAME);
    uniformNames.push_back(SHADER_NORMAL_MATRIX_NAME);
}
