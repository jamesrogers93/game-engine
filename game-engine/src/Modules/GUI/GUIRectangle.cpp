#include "game-engine/Modules/GUI/GUIRectangle.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

GUIRectangle::GUIRectangle(const glm::vec2 &bounds) : GUIShape() , bounds(bounds)
{
    initialise();
}

bool GUIRectangle::containsPoint(const float &x, const float &y)
{
    float halfX = this->bounds.x * 0.5;
    float halfY = this->bounds.y * 0.5;
    
    float left = this->position.x - (halfX);
    float right = this->position.x + (halfX);
    float bottom = this->position.y - (halfY);
    float top = this->position.y + (halfY);
    
    if(x > left && x < right &&
       y > bottom && y < top)
    {
        return true;
    }
    
    return false;
}

void GUIRectangle::initialise()
{
    
    // Create the GL stuff here to draw rectangle
    
    std::vector<VertexPU> vertices;
    
    glm::vec2 tempBounds = bounds * glm::vec2(0.5);
    VertexPU vertex1;
    vertex1.position = glm::vec3(-tempBounds.x, -tempBounds.y, 0.0);
    vertex1.uv0 = glm::vec2(0.0, 0.0);
    
    VertexPU vertex2;
    vertex2.position = glm::vec3(-tempBounds.x, tempBounds.y, 0.0);
    vertex2.uv0 = glm::vec2(0.0, 1.0);
    
    VertexPU vertex3;
    vertex3.position = glm::vec3(tempBounds.x, tempBounds.y, 0.0);
    vertex3.uv0 = glm::vec2(1.0, 1.0);
    
    VertexPU vertex4;
    vertex4.position = glm::vec3(tempBounds.x, -tempBounds.y, 0.0);
    vertex4.uv0 = glm::vec2(1.0, 0.0);
    
    
    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    vertices.push_back(vertex4);
    
    std::vector<unsigned int> indices;
    indices.push_back(0); indices.push_back(1); indices.push_back(2);
    indices.push_back(2); indices.push_back(3); indices.push_back(0);
    
    this->mesh = MeshGL::loadMeshGL(vertices, indices);
}
