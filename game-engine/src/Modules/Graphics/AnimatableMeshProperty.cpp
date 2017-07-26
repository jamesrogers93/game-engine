#include "game-engine/Modules/Graphics/AnimatableMeshProperty.h"

// STD
#include <algorithm>

// GLM
#include <glm/gtc/type_ptr.hpp>

// Game Engine Core
#include "game-engine/Core/GL/GL.h"

// Game Engine
#include "game-engine/Modules/Graphics/Shader.h"
#include "game-engine/Entity/Entity.h"

// Game Engine Defines
#include "game-engine/Defines/OpenGL.h"

#include "game-engine/Modules/Graphics/Graphics.h"
#include "game-engine/Util/StringUtil.h"

const unsigned int AnimatableMeshProperty::MAX_JOINTS = 60;
const std::string AnimatableMeshProperty::SHADER_JOINTS_NAME = "joints";

void AnimatableMeshProperty::setJointKeys(const std::vector<std::string> &keys)
{
    size_t numJoints = keys.size();
    
    for(unsigned int i = 0; i < numJoints; i++)
    {
        this->mJoints.push_back(toLower(keys[i]));
    }
    
    mJointUniformNames.empty();
    mJointUniformNames.reserve(numJoints);
    for(unsigned int i = 0; i < numJoints; i++)
    {
        mJointUniformNames.push_back(SHADER_JOINTS_NAME + "[" + std::to_string(i) + "]");
    }
}

void AnimatableMeshProperty::loadToShader(Shader *shader)
{
    // Call super class load to shader
    MeshProperty::loadToShader(shader);
    
    // Load joints to shader
    size_t numJoints = this->mJoints.size();
    for(unsigned int i = 0; i < numJoints; i++)
    {
        const GLint *loc = shader->getUniformLocation(mJointUniformNames[i]);
        if(loc != NULL)
        {
            glUniformMatrix4fv(*loc, 1, false, glm::value_ptr(mJointsPtrs[i]->getLocalModel()));
        } else
        {
            std::cout << "Problem!" << std::endl;
        }
    }
}

void AnimatableMeshProperty::linkJoints(Entity *entity)
{
    linkJoints2(entity);
    
    for(unsigned int i = 0; i < mJoints.size(); i++)
    {
        mJointsPtrs.push_back(mJointsMap.at(mJoints[i]));
    }
}

void AnimatableMeshProperty::linkJoints2(Entity *entity)
{
    // Search for this entity name in the joints keys
    std::vector<std::string>::iterator it = std::find(this->mJoints.begin(), this->mJoints.end(), entity->getName());
    
    if(it != this->mJoints.end())
    {
        // The entity name matches a key in mJoints!
        
        // Check if entity already exists in joint map
        if(this->mJointsMap.find(entity->getName()) == this->mJointsMap.end())
        {
            // Add it to the joints map
            this->mJointsMap[entity->getName()] = entity;
        }
        else
        {
            std::cout << "Already found joint. \n Infinite loop or multiple entites with same name?" << std::endl;
        }
    }
    else
    {
        //std::cout << "Should we be here?" << std::endl;
    }
    
    // Now recursivey look for the rest of the joint keys in the entity children
    const std::vector<Entity*> children = entity->getChildren();
    size_t numChildren = children.size();
    for(unsigned int i = 0; i < numChildren; i++)
    {
        linkJoints2(children[i]);
    }
}

/*bool AnimatableMeshProperty::makeActive()
{
    Property::makeActive();
    
    Graphics *g = &Graphics::getInstance();
    
    return g->addMeshProperty(this->mName, this);
}

bool AnimatableMeshProperty::makeUnactive()
{
    Property::makeUnactive();
    
    Graphics *g = &Graphics::getInstance();
    
    return g->removeMeshProperty(this->mName);
}*/

void AnimatableMeshProperty::fillUniformNames(std::vector<std::string> &uniformNames)
{
    MeshProperty::fillUniformNames(uniformNames);
    
    for(unsigned int i = 0; i < MAX_JOINTS; i++)
    {
        uniformNames.push_back(SHADER_JOINTS_NAME + "[" + std::to_string(i) + "]");
    }
    
}
