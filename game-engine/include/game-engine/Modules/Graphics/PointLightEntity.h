#ifndef _POINTLIGHTENTITY_H
#define _POINTLIGHTENTITY_H

#include "game-engine/Modules/Graphics/LightEntity.h"

#include <string>

struct Attenuation
{
    float constant, linear, quadratic;
    Attenuation(const float &constant, const float &linear, const float &quadratic) : constant(constant), linear(linear), quadratic(quadratic)
    {}
    
    // Default Attenuation values
    static const Attenuation ATT_7;
    static const Attenuation ATT_13;
    static const Attenuation ATT_20;
    static const Attenuation ATT_32;
    static const Attenuation ATT_50;
    static const Attenuation ATT_65;
    static const Attenuation ATT_100;
    static const Attenuation ATT_160;
    static const Attenuation ATT_200;
    static const Attenuation ATT_325;
    static const Attenuation ATT_600;
    static const Attenuation ATT_3250;
};

class PointLightEntity : public LightEntity
{
public:
    static const unsigned int MAX_LIGHTS;
private:
    static const std::string SHADER_POSITION_NAME;
    static const std::string SHADER_NUMLIGHTS_NAME;
    static const std::string SHADER_LIGHT_NAME;
    static const std::string SHADER_CONSTANT_NAME;
    static const std::string SHADER_LINEAR_NAME;
    static const std::string SHADER_QUADRATIC_NAME;
    
    Attenuation attenuation;
    
public:
    PointLightEntity(const std::string &name, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, const Attenuation &attenuation, const bool &on = DEFAULT_ON)
    : LightEntity(LightEntity::POINT, name, ambient, diffuse, specular, on), attenuation(attenuation)
    {}
    
    void loadToShader(Shader *shader, const unsigned int &index);
    static void loadNumLightsToShader(Shader *shader, const unsigned int &count);

    static void fillUniformNames(std::vector<std::string> &uniformNames);
};

#endif /* _POINTLIGHTENTITY_H */
