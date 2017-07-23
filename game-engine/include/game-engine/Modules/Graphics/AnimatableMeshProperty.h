#ifndef _ANIMATABLEMESHPROPERTY_H
#define _ANIMATABLEMESHPROPERTY_H

#include <vector>
#include <string>
#include <map>

#include "game-engine/Modules/Graphics/MeshProperty.h"
#include "game-engine/Modules/Graphics/Shader.h"

//class Shader;
class Entity;

class AnimatableMeshProperty : public MeshProperty
{
private:
    static const unsigned int MAX_JOINTS;
    static const std::string SHADER_JOINTS_NAME;
public:
    AnimatableMeshProperty(const std::string &name) : MeshProperty(name, Property::ANIMATABLE_MESH)
    {}
    
    ~AnimatableMeshProperty(){}
    
    //virtual bool makeActive();
    //virtual bool makeUnactive();
    
    const std::vector<std::string>& getJointKeys() const {   return this->mJoints;  }
    const std::map<std::string, Entity*> getLinkedJoints() const { return this->mJointsMap; }
    
    void setJointKeys(const std::vector<std::string> &keys);
    void linkJoints(Entity *root);
    
    void loadToShader(Shader *shader);
    static void fillUniformNames(std::vector<std::string> &uniformNames);
  
private:
    std::vector<std::string> mJoints; // Key to joints (mesh influences)
    std::map<std::string, Entity*> mJointsMap;
};

#endif /* _ANIMATABLEMESHPROPERTY_H */
