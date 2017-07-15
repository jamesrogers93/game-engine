#include "game-engine/Modules/Graphics/DirectionalLightEntity.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

// Game Engine Core
#include "game-engine/Modules/Graphics/Graphics.h"
#include "game-engine/Modules/Graphics/Shader.h"

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

const unsigned int DirectionalLightEntity::MAX_LIGHTS = 2;
const std::string DirectionalLightEntity::SHADER_NUMLIGHTS_NAME = "num_directional_lights";
const std::string DirectionalLightEntity::SHADER_LIGHT_NAME = "directional_lights[";
const std::string DirectionalLightEntity::SHADER_DIRECTION_NAME = "].direction";

void DirectionalLightEntity::loadToShader(Shader *shader, const unsigned int &index)
{
    std::string lightName = SHADER_LIGHT_NAME + std::to_string(index);
    
    // Direction
    GLint *loc = shader->getUniformLocation(lightName + SHADER_DIRECTION_NAME);
    if(loc != NULL)
    {
        glUniform3fv(*loc, 1, glm::value_ptr(this->direction));
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
}

void DirectionalLightEntity::loadNumLightsToShader(Shader *shader, const unsigned int &count)
{
    // Quadratic attenuation
    GLint *loc = shader->getUniformLocation(SHADER_NUMLIGHTS_NAME);
    if(loc != NULL)
    {
        glUniform1i(*loc, count);
    }
}

void DirectionalLightEntity::fillUniformNames(std::vector<std::string> &uniformNames)
{
    uniformNames.push_back(SHADER_NUMLIGHTS_NAME);
    
    for(unsigned int i = 0; i < MAX_LIGHTS; i++)
    {
        std::string lightName = SHADER_LIGHT_NAME + std::to_string(i);
        
        uniformNames.push_back(lightName + SHADER_DIRECTION_NAME);
        uniformNames.push_back(lightName + SHADER_AMBIENT_NAME);
        uniformNames.push_back(lightName + SHADER_DIFFUSE_NAME);
        uniformNames.push_back(lightName + SHADER_SPECULAR_NAME);
    }
}
