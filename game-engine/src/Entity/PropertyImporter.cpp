#include "game-engine/Entity/PropertyImporter.h"

#include "game-engine/Modules/Graphics/MeshProperty.h"
#include "game-engine/Modules/Graphics/AnimatableMeshProperty.h"

#include "game-engine/Util/StringUtil.h"

#include <iostream>
#include <sstream>
#include <vector>

const std::string PropertyImporter::MESH_TYPE = "mesh";
const std::string PropertyImporter::ANIMATABLE_MESH_TYPE = "animatable_mesh";

void PropertyImporter::ImportAsynchronously(const std::string &path)
{
    mThread = std::thread(&PropertyImporter::Import, this, path);
}

bool PropertyImporter::Import(const std::string &path)
{
    
    bool status;
    
    std::ifstream file;
    file.open(path, std::ios::binary);
    if (!file)
    {
        std::cout << "Unable to open file " << path << std::endl;
        return false;
    }
    
    
    std::string type;
    file >> type;
        
    if(type == MESH_TYPE)
    {
        readMeshProperty(file);
        status = true;
    }
    else if(type == ANIMATABLE_MESH_TYPE)
    {
        readAnimatableMeshProperty(file);
        status = true;
    }
    else
    {
        status =  false;
    }
    
    file.close();
    
    return status;
}

void PropertyImporter::readMeshProperty(std::ifstream &file)
{
    
    std::string name;
    file >> name;
    
    MeshProperty *property = new MeshProperty(name);
    
    std::string key;
    file >> key;
    
    if(key == "-G")
    {
        std::string meshKey;
        file >> meshKey;
        meshKey = toLower(meshKey);
        property->setMeshKey(meshKey);
        
        file >> key;
    }
    
    if(key == "-M")
    {
        std::string materialKey;
        file >> materialKey;
        materialKey = toLower(materialKey);
        property->setMaterialKey(materialKey);
        
        file >> key;
    }
    
    if(key == "-S")
    {
        std::string shaderKey;
        file >> shaderKey;
        shaderKey = toLower(shaderKey);
        property->setShaderKey(shaderKey);
    }
    
    this->importedObject = property;
    
}

void PropertyImporter::readAnimatableMeshProperty(std::ifstream &file)
{
    std::string name;
    file >> name;
    
    AnimatableMeshProperty *property = new AnimatableMeshProperty(name);
    
    std::string key;
    file >> key;
    
    if(key == "-G")
    {
        std::string meshKey;
        file >> meshKey;
        meshKey = toLower(meshKey);
        property->setMeshKey(meshKey);
        
        file >> key;
    }
    
    if(key == "-M")
    {
        std::string materialKey;
        file >> materialKey;
        materialKey = toLower(materialKey);
        property->setMaterialKey(materialKey);
        
        file >> key;
    }
    
    if(key == "-S")
    {
        std::string shaderKey;
        file >> shaderKey;
        shaderKey = toLower(shaderKey);
        property->setShaderKey(shaderKey);
        
        file >> key;
    }
    
    if(key == "-J")
    {
        std::string joints;
        file >> joints;
        
        std::stringstream strStream (joints);
        std::string segment;
        std::vector<std::string> jointsList;
        
        while(std::getline(strStream, segment, '$'))
        {
            jointsList.push_back(segment);
        }
        
        property->setJointKeys(jointsList);
    }
    
    this->importedObject = property;
}
