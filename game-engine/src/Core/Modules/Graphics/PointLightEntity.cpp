#include "game-engine/Core/Modules/Graphics/PointLightEntity.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

// Game Engine Core
#include "game-engine/Core/Modules/Graphics/Graphics.h"
#include "game-engine/Core/Modules/Graphics/Shader.h"

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

const Attenuation Attenuation::ATT_7 = Attenuation(1.0, 0.7, 1.8);
const Attenuation Attenuation::ATT_13 = Attenuation(1.0, 0.35, 0.44);
const Attenuation Attenuation::ATT_20 = Attenuation(1.0, 0.22, 0.20);
const Attenuation Attenuation::ATT_32 = Attenuation(1.0, 0.14, 0.07);
const Attenuation Attenuation::ATT_50 = Attenuation(1.0, 0.09, 0.032);
const Attenuation Attenuation::ATT_65  = Attenuation(1.0, 0.07, 0.017);
const Attenuation Attenuation::ATT_100 = Attenuation(1.0, 0.045, 0.0075);
const Attenuation Attenuation::ATT_160 = Attenuation(1.0, 0.027, 0.0028);
const Attenuation Attenuation::ATT_200 = Attenuation(1.0, 0.022, 0.0019);
const Attenuation Attenuation::ATT_325 = Attenuation(1.0, 0.014, 0.0007);
const Attenuation Attenuation::ATT_600 = Attenuation(1.0, 0.007, 0.0002);
const Attenuation Attenuation::ATT_3250 = Attenuation(1.0, 0.0014, 0.000007);

const unsigned int PointLightEntity::MAX_LIGHTS = 4;
const std::string PointLightEntity::SHADER_NUMLIGHTS_NAME = "num_point_lights";
const std::string PointLightEntity::SHADER_LIGHT_NAME = "point_lights[";
const std::string PointLightEntity::SHADER_POSITION_NAME = "].position";
const std::string PointLightEntity::SHADER_CONSTANT_NAME = "].constant";
const std::string PointLightEntity::SHADER_LINEAR_NAME = "].linear";
const std::string PointLightEntity::SHADER_QUADRATIC_NAME = "].quadratic";

void PointLightEntity::loadToShader(Shader *shader, const unsigned int &index)
{
    std::string lightName = SHADER_LIGHT_NAME + std::to_string(index);
    
    // Position
    GLint *loc = shader->getUniformLocation(lightName + SHADER_POSITION_NAME);
    if(loc != NULL)
    {
        glUniform3fv(*loc, 1, glm::value_ptr(this->position));
    }
    
    // Ambient colour
    loc = shader->getUniformLocation(lightName + SHADER_AMBIENT_NAME);
    if(loc != NULL)
    {
        glUniform4fv(*loc, 1, glm::value_ptr(glm::vec4(this->ambient, 1.0f)));
    }
    
    // Diffuse colour
    loc = shader->getUniformLocation(lightName + SHADER_DIFFUSE_NAME);
    if(loc != NULL)
    {
        glUniform4fv(*loc, 1, glm::value_ptr(glm::vec4(this->diffuse, 1.0f)));
    }
    
    // Specular colour
    loc = shader->getUniformLocation(lightName + SHADER_SPECULAR_NAME);
    if(loc != NULL)
    {
        glUniform4fv(*loc, 1, glm::value_ptr(glm::vec4(this->specular, 1.0f)));
    }
    
    // Constant attenuation
    loc = shader->getUniformLocation(lightName + SHADER_CONSTANT_NAME);
    if(loc != NULL)
    {
        glUniform1f(*loc, this->attenuation.constant);
    }
    
    // Linear attenuation
    loc = shader->getUniformLocation(lightName + SHADER_LINEAR_NAME);
    if(loc != NULL)
    {
        glUniform1f(*loc, this->attenuation.linear);
    }
    
    // Quadratic attenuation
    loc = shader->getUniformLocation(lightName + SHADER_QUADRATIC_NAME);
    if(loc != NULL)
    {
        glUniform1f(*loc, this->attenuation.quadratic);
    }
}

void PointLightEntity::loadNumLightsToShader(Shader *shader, const unsigned int &count)
{
    // Quadratic attenuation
    GLint *loc = shader->getUniformLocation(SHADER_NUMLIGHTS_NAME);
    if(loc != NULL)
    {
        glUniform1i(*loc, count);
    }
}

void PointLightEntity::fillUniformNames(std::vector<std::string> &uniformNames)
{
    uniformNames.push_back(SHADER_NUMLIGHTS_NAME);
    
    for(unsigned int i = 0; i < MAX_LIGHTS; i++)
    {
        std::string lightName = SHADER_LIGHT_NAME + std::to_string(i);
        
        uniformNames.push_back(lightName + SHADER_POSITION_NAME);
        uniformNames.push_back(lightName + SHADER_AMBIENT_NAME);
        uniformNames.push_back(lightName + SHADER_DIFFUSE_NAME);
        uniformNames.push_back(lightName + SHADER_SPECULAR_NAME);
        uniformNames.push_back(lightName + SHADER_CONSTANT_NAME);
        uniformNames.push_back(lightName + SHADER_LINEAR_NAME);
        uniformNames.push_back(lightName + SHADER_QUADRATIC_NAME);
    }
}

