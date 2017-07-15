#ifndef _ANIMATABLEMESHPROPERTY_H
#define _ANIMATABLEMESHPROPERTY_H

#include <vector>
#include <string>

#include "game-engine/Modules/Graphics/MeshProperty.h"

class Shader;

class AnimatableMeshProperty : public MeshProperty
{
    
public:
    AnimatableMeshProperty(const std::string &name) : MeshProperty(name, Property::ANIMATABLE_MESH)
    {}
    
    ~AnimatableMeshProperty(){}
    
    void initialise(){}
    void update(){}
    
    const std::vector<std::string>& getJointKeys() {   return this->mJoints;  }
    
    void setJointKeys(const std::vector<std::string> &keys) { this->mJoints = keys; }
    
    void loadToShader(Shader *shader);
    static void fillUniformNames(std::vector<std::string> &uniformNames);
  
private:
    std::vector<std::string> mJoints; // Key to joints (mesh influences)
};

#endif /* _ANIMATABLEMESHPROPERTY_H */
