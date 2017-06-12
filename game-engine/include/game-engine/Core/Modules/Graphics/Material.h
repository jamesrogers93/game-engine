#ifndef _MATERIAL_H
#define _MATERIAL_H

// STD
#include <string>

//GLM
#include <glm/glm.hpp>

class Material
{
private:
    static const float SHININESS_DEFAULT;
    
public:
    Material(std::string diffuseTexture, std::string specularTexture, float shininess = SHININESS_DEFAULT)
    : diffuseTexture(diffuseTexture), specularTexture(specularTexture), shininess(shininess)
    {}
    
    Material(glm::vec4 diffuseSolid, glm::vec4 specularSolid, float shininess = SHININESS_DEFAULT)
    : diffuseSolid(diffuseSolid), specularSolid(specularSolid), shininess(shininess)
    {}
    
    Material(std::string diffuseTexture, std::string specularTexture, glm::vec4 diffuseSolid, glm::vec4 specularSolid,  float shininess = SHININESS_DEFAULT)
    : diffuseTexture(diffuseTexture), specularTexture(specularTexture), diffuseSolid(diffuseSolid), specularSolid(specularSolid), shininess(shininess)
    {}
    
    ~Material()
    {}
    
private:
    std::string diffuseTexture, specularTexture;
    glm::vec4 diffuseSolid, specularSolid;
    float shininess;
};

#endif /* _MATERIAL_H */
