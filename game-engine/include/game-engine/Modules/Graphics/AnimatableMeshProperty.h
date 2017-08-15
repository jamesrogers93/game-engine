#ifndef _ANIMATABLEMESHPROPERTY_H
#define _ANIMATABLEMESHPROPERTY_H

#include <vector>
#include <string>
#include <unordered_map>

#include "game-engine/Modules/Graphics/MeshProperty.h"
#include "game-engine/Modules/Graphics/Shader.h"

// HACK
class JointEntity;
// END Hack

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
    const std::unordered_map<std::string, JointEntity*> getLinkedJoints() const { return this->mJointsMap; }
    
    void setJointKeys(const std::vector<std::string> &keys);
    void linkJoints(JointEntity *root);
    
    void loadToShader(Shader *shader);
    static void fillUniformNames(std::vector<std::string> &uniformNames);
  
private:
    std::vector<std::string> mJoints; // Key to joints (mesh influences)
    std::unordered_map<std::string, JointEntity*> mJointsMap; // This should be Entity, not JointEntity to keep the graphics and animation modules seperate. But this is needed and I have no time to redesign.
    std::vector<std::string> mJointUniformNames;
    std::vector<JointEntity*> mJointsPtrs;
    
    void linkJoints2(JointEntity *root);
};

#endif /* _ANIMATABLEMESHPROPERTY_H */
