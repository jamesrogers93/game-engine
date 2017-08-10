#include "game-engine/Entity/EntityImporter.h"

#include <iostream>

#include <glm/glm.hpp>

#include "game-engine/Modules/Animation/JointEntity.h"


const std::string EntityImporter::JOINT_TYPE = "joint";

void EntityImporter::ImportAsynchronously(const std::string &path)
{
    mThread = std::thread(&EntityImporter::Import, this, path);
}

bool EntityImporter::Import(const std::string &path)
{
    std::ifstream file;
    file.open(path, std::ios::binary);
    if (!file)
    {
        std::cout << "Unable to open file " << path << std::endl;
        return false;
    }
    
    while(!file.eof())
    {
        std::string type;
        file >> type;
        
        if(type == JOINT_TYPE)
        {
            readJoint(file);
        }
        
    }
    
    file.close();
    
    return true;
}

void EntityImporter::readJoint(std::ifstream &file)
{
    // Load in name
    std::string name;
    file >> name;
    
    // Load in parent
    std::string parent;
    file >> parent;
    
    // Load in local bind transform
    glm::mat4 localBindTransform;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            file >> localBindTransform[i][j];
        }
    }
    
    // Load in inverse bind transform
    glm::mat4 inverseBindTransform;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            file >> inverseBindTransform[i][j];
        }
    }
    
    
    // Now create joint entity
    
    JointEntity *joint = new JointEntity(name);
    
    // Add joint to imported entites
    if(this->importedEntites.find(name) == this->importedEntites.end())
    {
        this->importedEntites[name] = joint;
    }

    if(parent == "root")
    {
        this->importedObject = joint;
    }
    else
    {
        // Find parent in already processed entites
        if(this->importedEntites.find(parent) != this->importedEntites.end())
        {
            this->importedEntites[parent]->addChild(joint);
        }
        else
        {
            std::cout << "Problem!" << std::endl;
        }
        
    }
    
    joint->setLocalBindTransform(localBindTransform);
    joint->setInverseBindTransform(inverseBindTransform);
    //joint->transformOW(bindPose);
    //joint->setInverseBindPose(inverseBindPose);
    
}
