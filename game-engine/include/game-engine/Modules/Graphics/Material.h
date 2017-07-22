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
    
    std::string name;
    
    std::string diffuseTexture, specularTexture;
    glm::vec4 diffuseSolid, specularSolid;
    float shininess;
    
    bool isDiffuseTexture, isSpecularTexture;
    bool isDiffuseSolid, isSpecularSolid;
    
public:
    Material(const std::string &name, const std::string &diffuseTexture, const std::string &specularTexture, const float &shininess = SHININESS_DEFAULT)
    : name(name), diffuseTexture(diffuseTexture), specularTexture(specularTexture), shininess(shininess), isDiffuseTexture(true), isSpecularTexture(true), isDiffuseSolid(false), isSpecularSolid(false)
    {}
    
    Material(const std::string &name, const glm::vec4 &diffuseSolid, const glm::vec4 &specularSolid, const float &shininess = SHININESS_DEFAULT)
    : name(name), diffuseSolid(diffuseSolid), specularSolid(specularSolid), shininess(shininess), isDiffuseTexture(false), isSpecularTexture(false), isDiffuseSolid(true), isSpecularSolid(true)
    {}
    
    Material(const std::string &name, const std::string &diffuseTexture, const std::string &specularTexture, const glm::vec4 &diffuseSolid, const glm::vec4 &specularSolid, const float &shininess = SHININESS_DEFAULT)
    : name(name), diffuseTexture(diffuseTexture), specularTexture(specularTexture), diffuseSolid(diffuseSolid), specularSolid(specularSolid), shininess(shininess), isDiffuseTexture(true), isSpecularTexture(true), isDiffuseSolid(true), isSpecularSolid(true)
    {}
    
    ~Material()
    {}
    
    const std::string& getName() const { return name; }
    
    bool loadToShader(Shader *shader);
    
    static void fillUniformNames(std::vector<std::string> &uniformNames);
    
    std::string getDiffuseTexture() const { return this->diffuseTexture; }
    std::string getSpecularTexture() const { return this->specularTexture; }
    glm::vec4 getDiffuseSolid() const { return this->diffuseSolid; }
    glm::vec4 getSpecularSolid() const { return this->specularSolid; }
    float getShininess() const { return this->shininess; }
    
    bool hasDiffuseTexture() const { return isDiffuseTexture; }
    bool hasSpecularTexture() const { return isSpecularTexture; }
    bool hasDiffuseSolid() const { return isDiffuseSolid; }
    bool hasSpecularSolid() const { return isSpecularSolid; }
    
};

#endif /* _MATERIAL_H */
