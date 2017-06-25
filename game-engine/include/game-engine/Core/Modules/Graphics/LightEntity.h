#ifndef _LIGHTENTITY_H
#define _LIGHTENTITY_H

// STD
#include <string>
#include <vector>

// Engine
#include "game-engine/Core/Entity/ENode.h"

// GLM
#include <glm/glm.hpp>

class Shader;

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

class LightEntity : public ENode
{
private:
    static const std::string SHADER_NUMLIGHTS_NAME;
    static const std::string SHADER_LIGHT_NAME;
    static const std::string SHADER_POSITION_NAME;
    static const std::string SHADER_AMBIENT_NAME;
    static const std::string SHADER_DIFFUSE_NAME;
    static const std::string SHADER_SPECULAR_NAME;
    static const std::string SHADER_CONSTANT_NAME;
    static const std::string SHADER_LINEAR_NAME;
    static const std::string SHADER_QUADRATIC_NAME;
    
public:
    
    LightEntity(const std::string &name, const glm::vec3 &position, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, const Attenuation &attenuation) : ENode(name, position), on(true), ambient(ambient), diffuse(diffuse), specular(specular), attenuation(attenuation){}
    
    void attachToEngine();
    
    void loadToShader(Shader *shader, const unsigned int &index);
    static void loadNumLightsToShader(Shader *shader, const unsigned int &count);
    
    void turnOn();
    void turnOff();
    const bool& isOn();
    
    static void fillUniformNames(std::vector<std::string> &uniformNames);
    
private:
    bool on;
    glm::vec3 ambient, diffuse, specular;
    Attenuation attenuation;
};

# endif /* _LIGHTENTITY_H */
