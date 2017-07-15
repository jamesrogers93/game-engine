#ifndef _DIRECTIONALLIGHTENTITY_H
#define _DIRECTIONALLIGHTENTITY_H

#include "game-engine/Modules/Graphics/LightProperty.h"

#include <string>

class DirectionalLightProperty : public LightProperty
{
public:
    static const unsigned int MAX_LIGHTS;
private:
    static const std::string SHADER_DIRECTION_NAME;
    static const std::string SHADER_NUMLIGHTS_NAME;
    static const std::string SHADER_LIGHT_NAME;
    
    glm::vec3 direction;
    
public:
    DirectionalLightProperty(const std::string &name, const glm::vec3 &direction, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, const bool &on = DEFAULT_ON)
    : LightProperty(LightProperty::DIRECTIONAL, name, ambient, diffuse, specular, on), direction(direction)
    {}

    void loadToShader(Shader *shader, const unsigned int &index);
    static void loadNumLightsToShader(Shader *shader, const unsigned int &count);
    
    static void fillUniformNames(std::vector<std::string> &uniformNames);
};

#endif /* _DIRECTIONALLIGHTENTITY_H */
