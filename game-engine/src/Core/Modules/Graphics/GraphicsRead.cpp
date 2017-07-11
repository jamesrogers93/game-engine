#include "game-engine/Core/Modules/Graphics/GraphicsRead.h"

#include "game-engine/Core/Modules/Graphics/Graphics.h"
#include "game-engine/Core/Modules/Graphics/Vertex.h"
#include "game-engine/Core/Modules/Graphics/Geometry.h"

#include <iostream>
#include <map>
#include <vector>

const std::string GraphicsRead::GEOMETRY_TYPE = "GEOMETRY";

bool GraphicsRead::readJMPFile(const std::string &filePath)
{
    
    // Open the JMP file
    std::ifstream file;
    file.open(filePath);
    if (!file)
    {
        std::cout << "Unable to open file " << filePath << std::endl;
        return false;
    }
    
    while(!file.eof())
    {
        std::string type;
        file >> type;
    
        if(type == GEOMETRY_TYPE)
        {
            readGeometry(file);
        }
    }
    
    file.close();
    
    return true;
}

void GraphicsRead::readGeometry(std::ifstream &file)
{
    // Read geomety name
    std::string name;
    file >> name;
    
    // Read types of vertex information
    std::map<std::string, unsigned int> sources;
    char rowType;
    while(file >> rowType && rowType == 'S')
    {
        std::string sourceType;
        unsigned int sourceStride;
        
        file >> sourceType >> sourceStride;
        
        sources[sourceType] = sourceStride;
    }
    
    std::vector<Vertex> vertices;
    
    if(rowType == 'V')
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
            
            vertices.push_back(vert);
        }
    }
    
    std::vector<unsigned int> indices;
    file >> rowType;
    if(rowType == 'I')
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
    
    Geometry *g = Geometry::loadGeometry(vertices, indices);
    
    Graphics::getInstance().addGeometry(name, g);
}
