#ifndef _MATERIAL_H
#define _MATERIAL_H

// STD
#include <string>
#include <vector>

//GLM
#include <glm/glm.hpp>

class Shader;

class Material
{
private:
    static const float SHININESS_DEFAULT;
    
    static const std::string SHADER_DIFF_TEX_NAME;
    static const std::string SHADER_SPEC_TEX_NAME;
    static const std::string SHADER_DIFF_SOLID_NAME;
    static const std::string SHADER_SPEC_SOLID_NAME;
    static const std::string SHADER_SHININESS_NAME;
    
public:
    Material(const std::string &diffuseTexture, const std::string &specularTexture, const float &shininess = SHININESS_DEFAULT)
    : diffuseTexture(diffuseTexture), specularTexture(specularTexture), shininess(shininess), isDiffuseTexture(true), isSpecularTexture(true), isDiffuseSolid(false), isSpecularSolid(false)
    {}
    
    Material(const glm::vec4 &diffuseSolid, const glm::vec4 &specularSolid, const float &shininess = SHININESS_DEFAULT)
    : diffuseSolid(diffuseSolid), specularSolid(specularSolid), shininess(shininess), isDiffuseTexture(false), isSpecularTexture(false), isDiffuseSolid(true), isSpecularSolid(true)
    {}
    
    Material(const std::string &diffuseTexture, const std::string &specularTexture, const glm::vec4 &diffuseSolid, const glm::vec4 &specularSolid, const float &shininess = SHININESS_DEFAULT)
    : diffuseTexture(diffuseTexture), specularTexture(specularTexture), diffuseSolid(diffuseSolid), specularSolid(specularSolid), shininess(shininess), isDiffuseTexture(true), isSpecularTexture(true), isDiffuseSolid(true), isSpecularSolid(true)
    {}
    
    ~Material()
    {}
    
    bool loadToShader(Shader *shader);
    
    static void fillUniformNames(std::vector<std::string> &uniformNames);
    
private:
    
    std::string diffuseTexture, specularTexture;
    glm::vec4 diffuseSolid, specularSolid;
    float shininess;
    
    bool isDiffuseTexture, isSpecularTexture;
    bool isDiffuseSolid, isSpecularSolid;
};

#endif /* _MATERIAL_H */