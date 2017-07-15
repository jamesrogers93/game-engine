#ifndef _LIGHTENTITY_H
#define _LIGHTENTITY_H

// STD
#include <string>
#include <vector>

// Engine
#include "game-engine/Entity/Property.h"

// GLM
#include <glm/glm.hpp>

class Shader;

class LightProperty : public Property
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
    
    LightProperty(const Type &type, const std::string &name, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, const bool &on = DEFAULT_ON) : Property(name), ambient(ambient), diffuse(diffuse), specular(specular), on(on), type(type)
    {}
    
public:
    
    Type getType() const;
    
    void initialise();
    void update(){}
    
    virtual void loadToShader(Shader *shader, const unsigned int &index) = 0;
    
    void turnOn();
    void turnOff();
    const bool& isOn();
    
};

# endif /* _LIGHTENTITY_H */
