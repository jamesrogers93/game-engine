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
    
    MeshProperty(const std::string &name, const Type &type) : Property(name, type), mMeshKeySet(false), mMaterialKeySet(false), mShaderKeySet(false)
    {}
    
public:
    MeshProperty(const std::string &name) : Property(name, Property::MESH)
    {}
    
    ~MeshProperty(){}
    
    virtual void initialise();
    virtual void update(){}
    
    const std::string& getMeshKey() const {   return this->mMesh;  }
    const std::string& getMaterialKey() const {   return this->mMaterial;  }
    const std::string& getShaderKey() const {   return this->mShader;  }
    
    void setMeshKey(const std::string &key) { this->mMesh = key; mMeshKeySet = true; }
    void setMaterialKey(const std::string &key) { this->mMaterial = key; mMaterialKeySet = true; }
    void setShaderKey(const std::string &key) { this->mShader = key; mShaderKeySet = true; }
    
    const bool& hasMeshKey() const { return mMeshKeySet; }
    const bool& hasMaterialKey() const { return mMaterialKeySet; }
    const bool& hasShaderKey() const { return mShaderKeySet; }
    
    virtual void loadToShader(Shader *shader);
    static void fillUniformNames(std::vector<std::string> &uniformNames);
    
private:
    std::string mMesh;   // Key to geometry in Graphics
    std::string mMaterial;   // Key to material in Graphics
    std::string mShader;     // Key to shader in Graphics
    
    bool mMeshKeySet;
    bool mMaterialKeySet;
    bool mShaderKeySet;
};

#endif /* _GRAPHICSENTITY_H */
