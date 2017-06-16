#ifndef _GRAPHICSENTITY_H
#define _GRAPHICSENTITY_H

// STD
#include <string>

// Game Engine Core
#include "game-engine/Core/Entity/ENode.h"

class Shader;

class GeometryEntity : public ENode
{
public:
    GeometryEntity(const std::string &name, const glm::vec3 &position, const std::string &geometryKey, const std::string &materialKey, const std::string &shaderKey)
    : ENode(name, position), geometry(geometryKey), material(materialKey), shader(shaderKey)
    {}
    
    GeometryEntity(const std::string &name, const float &posX, const float &posY, const float &posZ, const std::string &geometryKey, const std::string &materialKey, const std::string &shaderKey)
    : ENode(name, glm::vec3(posX, posY, posZ)), geometry(geometryKey), material(materialKey), shader(shaderKey)
    {}
    
    ~GeometryEntity(){}
    
    const std::string& getGeometryKey() {   return this->geometry;  }
    const std::string& getMaterialKey() {   return this->material;  }
    const std::string& getShaderKey() {   return this->shader;  }
    
    void loadToShader(Shader *shader);
    
private:
    std::string geometry;   // Key to geometry in Graphics
    std::string material;   // Key to material in Graphics
    std::string shader;     // Key to shader in Graphics
    
    void attachToEngine();
};

#endif /* _GRAPHICSENTITY_H */
