#include "game-engine/Modules/Graphics/MaterialImporter.h"

#include <iostream>
#include <fstream>

#include <glm/glm.hpp>

#include "game-engine/Modules/Graphics/Material.h"

void MaterialImporter::ImportAsynchronously(const std::string &path)
{
    mThread = std::thread(&MaterialImporter::Import, this, path);
}

bool MaterialImporter::Import(const std::string &path)
{
    
    std::ifstream file;
    file.open(path);
    if (!file)
    {
        std::cout << "Unable to open file " << path << std::endl;
        return false;
    }
    
        std::string name;
        file >> name;
        
        glm::vec4 diffuseSolid;
        glm::vec4 specularSolid;
        float shininess;
        
        std::string type;
        file >> type;
        if(type == "-DS")
        {
            float r, g, b, a;
            file >> r >> g >> b >> a;
            diffuseSolid = glm::vec4(r, g, b, a);
            file >> type;
        }
        
        if(type == "-SS")
        {
            float r, g, b, a;
            file >> r >> g >> b >> a;
            specularSolid = glm::vec4(r, g, b, a);
            file >> type;
        }
        
        if(type == "-S")
        {
            file >> shininess;
        }
        
        Material *m = new Material(name, diffuseSolid, specularSolid, shininess);
        
        
        this->importedObject = m;
    
    file.close();
    
    return true;
}
