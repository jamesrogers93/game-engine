#include "game-engine/Modules/GUI/GUICircle.h"

const unsigned int GUICircle::TRIANGLES = 1;

GUICircle::GUICircle(const float &radius) : GUIShape() , radius(radius)
{
    initialise();
}

bool GUICircle::containsPoint(const float &x, const float &y)
{
    glm::vec2 point(x,y);
    
    float distance = glm::length(point - position);
    
    if((distance * distance) < (radius * radius))
    {
        return true;
    }
    
    return false;
}

void GUICircle::initialise()
{
    
    // Create the GL stuff here
    float doublePi = M_PI * 2.0;
    
    // Change the number of triangles based on the radius
    float triangles = TRIANGLES * radius;
    
    std::vector<VertexPU> vertices;
    
    // Center of circle
    VertexPU center;
    center.position = glm::vec3(0.0f);
    center.uv0 = glm::vec2(0.5f);

    float denom = radius - - radius;
    float iDenom = 1 / denom;
    
    // Create vertices
    for(int i = 0; i <= triangles; i++)
    {
        float x = radius * cos(i * doublePi / triangles);
        float y = radius * sin(i * doublePi / triangles);
        float z = 0.0f;
        
        float u = (x - - radius) * iDenom;
        float v = (y - - radius) * iDenom;
        
        VertexPU vertex;
        vertex.position = glm::vec3(x, y, z);
        vertex.uv0 = glm::vec2(u, v);
        
        vertices.push_back(vertex);
    }
    
    //Create vertex indices
    std::vector<unsigned int> indices;
    for(int i = 0; i < triangles; i++)
    {
        indices.push_back(0); //origin index
        indices.push_back(i+1);
        indices.push_back(i+2);
    }
    
    mesh = MeshGL::loadMeshGL(vertices, indices);
    
}
