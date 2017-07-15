#ifndef _ANIMATABLE_H
#define _ANIMATABLE_H

#include <vector>
#include <string>

#include "game-engine/Entity/Property.h"

class Shader;

class AnimatableMeshProperty : public Property
{
private:
    static const std::string SHADER_MODEL_NAME;
    static const std::string SHADER_NORMAL_MATRIX_NAME;
    
public:
    AnimatableMeshProperty(const std::string &name);
    
    ~AnimatableMeshProperty(){}
    
    void initialise(){}
    void update(){}
    
    const std::string& getGeometryKey() {   return this->mGeometry;  }
    const std::string& getMaterialKey() {   return this->mMaterial;  }
    const std::string& getShaderKey() {   return this->mShader;  }
    const std::vector<std::string>& getJointKeys() {   return this->mJoints;  }
    
    void setGeometryKey(const std::string &key) { this->mGeometry = key; }
    void setMaterialKey(const std::string &key) { this->mMaterial = key; }
    void setShaderKey(const std::string &key) { this->mShader = key; }
    void setJointKeys(const std::vector<std::string> &keys) { this->mJoints = keys; }
    
    void loadToShader(Shader *shader);
    static void fillUniformNames(std::vector<std::string> &uniformNames);
  
private:
    std::string mGeometry;   // Key to geometry
    std::string mMaterial;   // Key to material
    std::string mShader;     // Key to shader
    std::vector<std::string> mJoints; // Key to joints (mesh inflences)
};

#endif /* _ANIMATABLE_H */
