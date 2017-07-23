#include "game-engine/Modules/Graphics/MeshImporter.h"

#include <iostream>
#include <fstream>
#include <map>

#include <glm/glm.hpp>

#include "game-engine/Modules/Graphics/Mesh.h"

void MeshImporter::ImportAsynchronously(const std::string &path)
{
    mThread = std::thread(&MeshImporter::Import, this, path);
}

bool MeshImporter::Import(const std::string &path)
{
    
    std::ifstream file;
    file.open(path);
    if (!file)
    {
        std::cout << "Unable to open file " << path << std::endl;
        return false;
    }
    
    readMesh(file);
    
    file.close();
    
    return true;
}

void MeshImporter::readMesh(std::ifstream &file)
{
    // Read geomety name
    std::string name;
    file >> name;
    
    // Read types of vertex information
    std::map<std::string, unsigned int> sources;
    std::string rowType;
    while(file >> rowType && rowType == "-S")
    {
        std::string sourceType;
        unsigned int sourceStride;
        
        file >> sourceType >> sourceStride;
        
        sources[sourceType] = sourceStride;
    }
    
    std::vector<Vertex> vertices;
    
    if(rowType == "-V")
    {
        unsigned int numVertices;
        file >> numVertices;
        
        for(int i = 0; i < numVertices; i++)
        {
            Vertex vert;
            
            if(sources.find("position") != sources.end())
            {
                float x, y, z;
                file >> x >> y >> z;
                
                vert.setPosition(glm::vec3(x, y, z));
            }
            
            if(sources.find("normal") != sources.end())
            {
                float x, y, z;
                file >> x >> y >> z;
                
                vert.setNormal(glm::vec3(x, y, z));
            }
            
            if(sources.find("uv0") != sources.end())
            {
                float u, v;
                file >> u >> v;
                
                vert.setUV0(glm::vec2(u, v));
            }
            
            if(sources.find("colour") != sources.end())
            {
                float r, g, b, a;
                file >> r >> g >> b >> a;
                
                vert.setColour(glm::vec4(r, g, b, a));
            }
            
            if(sources.find("joint_id") != sources.end())
            {
                float x, y, z, w;
                file >> x >> y >> z >> w;
                
                vert.setJointId(glm::vec4(x, y, z, w));
            }
            
            if(sources.find("joint_weight") != sources.end())
            {
                float x, y, z, w;
                file >> x >> y >> z >> w;
                
                vert.setJointWeight(glm::vec4(x, y, z, w));
            }
            vertices.push_back(vert);
        }
    }
    
    std::vector<unsigned int> indices;
    file >> rowType;
    if(rowType == "-I")
    {
        unsigned int numIndices;
        file >> numIndices;
        
        for(int i = 0; i < numIndices; i++)
        {
            unsigned int index;
            file >> index;
            
            indices.push_back(index);
        }
    }
    
    Mesh *mesh =  new Mesh(name, vertices, indices);
    
    this->importedObject = mesh;
    
}
