#ifndef _MESHPROPERTY_H
#define _MESHPROPERTY_H

// STD
#include <string>

// Game Engine Core
#include "game-engine/Entity/Entity.h"

class Shader;

class MeshProperty : public Entity
{
private:
    static const std::string SHADER_MODEL_NAME;
    static const std::string SHADER_NORMAL_MATRIX_NAME;
    
public:
    MeshProperty(const std::string &name, const std::string &geometryKey, const std::string &materialKey, const std::string &shaderKey);
    
    ~MeshProperty(){}
    
    void initialise();
    void update(){}
    
    const std::string& getGeometryKey() {   return this->geometry;  }
    const std::string& getMaterialKey() {   return this->material;  }
    const std::string& getShaderKey() {   return this->shader;  }
    
    void loadToShader(Shader *shader);
    static void fillUniformNames(std::vector<std::string> &uniformNames);
    
private:
    std::string geometry;   // Key to geometry in Graphics
    std::string material;   // Key to material in Graphics
    std::string shader;     // Key to shader in Graphics
};

#endif /* _GRAPHICSENTITY_H */
