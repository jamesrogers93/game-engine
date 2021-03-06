#ifndef _MESHPROPERTY_H
#define _MESHPROPERTY_H

// STD
#include <string>
#include <vector>

// Game Engine Core
#include "game-engine/Core/Main/Property.h"

// OpenGL
#include "game-engine/Core/GL/OpenGL.h"

class Shader;
class MeshGL;
class Material;

class MeshProperty : public Property
{
protected:
    static const std::string SHADER_MODEL_NAME;
    static const std::string SHADER_NORMAL_MATRIX_NAME;
    
    MeshProperty(const std::string &name, const Type &type) : Property(name, type), mMeshKeySet(false), mMaterialKeySet(false), mShaderKeySet(false), drawMode(GL_TRIANGLES)
    {}
    
public:
    MeshProperty(const std::string &name) : Property(name, Property::MESH), drawMode(GL_TRIANGLES)
    {}
    
    ~MeshProperty(){}
    
    bool makeActive();
    bool makeUnactive();
    //virtual void initialise();
    //virtual void update(){}
    
    const std::string& getMeshKey() const {   return this->mMesh;  }
    const std::string& getMaterialKey() const {   return this->mMaterial;  }
    const std::string& getShaderKey() const {   return this->mShader;  }
    
    const MeshGL* getMeshPtr() const { return mMeshPtr; }
    const Material* getMaterialPtr() const { return mMaterialPtr; }
    const Shader* getShaderPtr() const { return mShaderPtr; }
    
    void setMeshKey(const std::string &key) { this->mMesh = key; mMeshKeySet = true; }
    void setMaterialKey(const std::string &key) { this->mMaterial = key; mMaterialKeySet = true; }
    void setShaderKey(const std::string &key) { this->mShader = key; mShaderKeySet = true; }
    
    const bool& hasMeshKey() const { return mMeshKeySet; }
    const bool& hasMaterialKey() const { return mMaterialKeySet; }
    const bool& hasShaderKey() const { return mShaderKeySet; }
    
    virtual void loadToShader(Shader *shader);
    static void fillUniformNames(std::vector<std::string> &uniformNames);
    
    void setDrawMode(const int &flag) {drawMode = flag; }
    
    const int getDrawMode() { return drawMode; }
    
    void linkMeshPtr();
    void linkMaterialPtr();
    void linkShaderPtr();
    
private:
    std::string mMesh;   // Key to geometry in Graphics
    std::string mMaterial;   // Key to material in Graphics
    std::string mShader;     // Key to shader in Graphics
    
    const MeshGL *mMeshPtr;           //
    const Material *mMaterialPtr;     //  These are linked during makeActive() method to eliminate look ups every frame
    const Shader *mShaderPtr;         //
    
    bool mMeshKeySet;
    bool mMaterialKeySet;
    bool mShaderKeySet;
    
    int drawMode;
    
    
};

#endif /* _GRAPHICSENTITY_H */
