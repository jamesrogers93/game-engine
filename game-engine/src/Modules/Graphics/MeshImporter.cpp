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
    file.open(path, std::ios::binary);
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
    std::map<std::string, bool> sources;
    std::string rowType;
    unsigned int numVertexElements = 0;
    while(file >> rowType && rowType == "-S")
    {
        std::string sourceType;
        unsigned int sourceStride;
        
        file >> sourceType >> sourceStride;
        
        sources[sourceType] = true;
        
        numVertexElements += sourceStride;
    }
    
    if(sources["position"] && sources["normal"] && sources["uv0"] && sources["joint_id"] && sources["joint_weight"])
    {
        //std::vector<VertexPNUJ> vertices;
    }
    else
    {
        std::cout << " Error: Unsupported vertex sources" << std::endl;
        return;
    }
    
    std::vector<VertexPNUJ> vertices;
    
    std::cout << "starting" << std::endl;
    if(rowType == "-V")
    {
        unsigned int numVertices;
        file >> numVertices;
        
        // Read vertex data
        //file.seekg(1, std::ios::cur);
        //std::vector<float> v(numVertices);
        
        //file.read(reinterpret_cast<char*> (&v[0]), numVertices * sizeof(float));
        
        
        // HARD CODE FOR NOW. MUST CHANGE!!!!!!!
        // Read vertex data
        file.seekg(1, std::ios::cur);
        vertices.resize(numVertices);
        file.read(reinterpret_cast<char*> (&vertices[0]), numVertices * sizeof(VertexPNUJ));
    }
    std::cout << "ending" << std::endl;
    
    std::vector<unsigned int> indices;
    file >> rowType;
    if(rowType == "-I")
    {
        unsigned int numIndices;
        file >> numIndices;
        
        file.seekg(1, std::ios::cur);
        indices.resize(numIndices);
        file.read(reinterpret_cast<char*> (&indices[0]), numIndices * sizeof(unsigned int));

    }
    
    Mesh *mesh =  new Mesh(name, vertices, indices);
    
    this->importedObject = mesh;
    
}
