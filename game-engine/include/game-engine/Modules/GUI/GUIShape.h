#ifndef _GUISHAPE_H
#define _GUISHAPE_H

#include <glm/glm.hpp>

// Should move this to Core/GL
#include "game-engine/Modules/Graphics/Mesh.h"
#include "game-engine/Modules/Graphics/Vertex.h"
#include "game-engine/Modules/Graphics/Shader.h"

class GUIShape
{
protected:
    
    MeshGL *mesh;
public:
    
    glm::vec2 position;
    glm::vec4 colour;
    
    GUIShape()
    {}
    
    void translateOW(const glm::vec2 &position) { this->position = position; }
    void translate(const glm::vec2 &position) { this->position += position; }
    void setColour(const glm::vec4 &colour) { this->colour = colour; }

    virtual void draw(Shader *shader) = 0;
    
    virtual bool containsPoint(const float &x, const float &y) = 0;
    
};

#endif /* _GUISHAPE_H */
