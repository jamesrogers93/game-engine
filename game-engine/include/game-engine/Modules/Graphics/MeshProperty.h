#ifndef _MESHPROPERTY_H
#define _MESHPROPERTY_H

// STD
#include <string>

// Game Engine Core
#include "game-engine/Entity/Property.h"

class Shader;

class MeshProperty : public Property
{
protected:
    static const std::string SHADER_MODEL_NAME;
    static const std::string SHADER_NORMAL_MATRIX_NAME;
    
    MeshProperty(const std::string &name, const Type &type) : Property(name, type)
    {}
    
public:
    MeshProperty(const std::string &name) : Property(name, Property::MESH)
    {}
    
    ~MeshProperty(){}
    
    virtual void initialise();
    virtual void update(){}
    
    const std::string& getGeometryKey() {   return this->mGeometry;  }
    const std::string& getMaterialKey() {   return this->mMaterial;  }
    const std::string& getShaderKey() {   return this->mShader;  }
    
    void setGeometryKey(const std::string &key) { this->mGeometry = key; }
    void setMaterialKey(const std::string &key) { this->mMaterial = key; }
    void setShaderKey(const std::string &key) { this->mShader = key; }
    
    virtual void loadToShader(Shader *shader);
    static void fillUniformNames(std::vector<std::string> &uniformNames);
    
private:
    std::string mGeometry;   // Key to geometry in Graphics
    std::string mMaterial;   // Key to material in Graphics
    std::string mShader;     // Key to shader in Graphics
};

#endif /* _GRAPHICSENTITY_H */
