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



class LightEntity : public ENode
{
public:
    enum Type
    {
        POINT, DIRECTIONAL, UNDEFINED
    };
protected:
    static const std::string SHADER_AMBIENT_NAME;
    static const std::string SHADER_DIFFUSE_NAME;
    static const std::string SHADER_SPECULAR_NAME;
    
    static const bool DEFAULT_ON;
    
    glm::vec3 ambient, diffuse, specular;
    bool on;
    Type type;
    
    LightEntity(const Type &type, const std::string &name, const glm::vec3 &position, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, const bool &on = DEFAULT_ON) : ENode(name, position), ambient(ambient), diffuse(diffuse), specular(specular), on(on), type(type)
    {}
    
    LightEntity(const Type &type, const std::string &name, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, const bool &on = DEFAULT_ON) : ENode(name), ambient(ambient), diffuse(diffuse), specular(specular), on(on), type(type)
    {}
    
public:
    
    Type getType() const;
    
    void attachToEngine();
    
    virtual void loadToShader(Shader *shader, const unsigned int &index) = 0;
    
    void turnOn();
    void turnOff();
    const bool& isOn();
    
};

# endif /* _LIGHTENTITY_H */
