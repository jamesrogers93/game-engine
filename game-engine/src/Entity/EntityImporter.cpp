#include "game-engine/Entity/EntityImporter.h"

#include <iostream>

#include <glm/glm.hpp>

#include "game-engine/Modules/Animation/JointEntity.h"

const std::string EntityImporter::JOINT_TYPE = "joint";

bool EntityImporter::Import(const std::string &path)
{
    
    std::ifstream file;
    file.open(path);
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
    
    // Load in inverseBindPose
    glm::mat4 bindPose;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            file >> bindPose[i][j];
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
    
    joint->transformOW(bindPose);
    //joint->setInverseBindPose(inverseBindPose);
    
}
