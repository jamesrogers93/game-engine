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
}

void AnimatableMeshProperty::loadToShader(Shader *shader)
{
    // Call super class load to shader
    MeshProperty::loadToShader(shader);
    
    // Load joints to shader
    for(unsigned int i = 0; i < this->mJoints.size(); i++)
    {
        GLint *loc =shader->getUniformLocation(SHADER_JOINTS_NAME + "[" + std::to_string(i) + "]");
        if(loc != NULL)
        {
            if(this->mJointsMap.find(this->mJoints[i]) != this->mJointsMap.end())
            {
                Entity *joint = this->mJointsMap[this->mJoints[i]];
                const glm::mat4 *jointTransform = &joint->getLocalModel();
                
                //if(joint->getLocalTransformUpdate().getFlag())
                //{
                    //glUniformMatrix4fv(*loc, 1, false, glm::value_ptr(*jointTransform));
                //    joint->getLocalTransformUpdate().reset();
                //}
                
                
                //jmpGLUniformMatrix4fv(joint->getLocalTransformUpdate(), shader->getProgram(), *loc, 1, false, glm::value_ptr(*jointTransform));
                jmpGLUniformMatrix4fv(shader->getProgram(), *loc, 1, false, glm::value_ptr(*jointTransform));
            }
        } else
        {
            std::cout << "Problem!" << std::endl;
        }
    }
}

void AnimatableMeshProperty::linkJoints(Entity *entity)
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
        linkJoints(children[i]);
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
