#ifndef _GUISHAPE_H
#define _GUISHAPE_H

#include <glm/glm.hpp>

// Should move this to Core/GL
#include "game-engine/Modules/Graphics/Mesh.h"
#include "game-engine/Modules/Graphics/Vertex.h"
#include "game-engine/Modules/Graphics/Shader.h"

#include "game-engine/Core/GL/GLTexture.h"

class GUIShape
{
protected:
    
    static const int COLOUR_BIT = 0x01;
    static const int COLOUR_MAP_BIT = 0x02;
    
    MeshGL *mesh;
public:
    
    glm::vec2 position;
    glm::vec4 colourUp;
    glm::vec4 colourDown;
    GLTexture colourMapUp;
    GLTexture colourMapDown;
    
    bool colourUpSet;
    bool colourDownSet;
    bool colourMapUpSet;
    bool colourMapDownSet;
    
    int colourUpBitwise;
    int colourDownBitwise;
    
    bool isDown;
    
    
    GUIShape() : colourUpSet(false), colourDownSet(false), colourMapUpSet(false), colourMapDownSet(false), colourUpBitwise(0), colourDownBitwise(0), isDown(false)
    {}
    
    void translateOW(const glm::vec2 &position) { this->position = position; }
    void translate(const glm::vec2 &position) { this->position += position; }
    void setColourUp(const glm::vec4 &colour);
    void setColourDown(const glm::vec4 &colour);
    void setMapUp(const GLTexture &map);
    void setMapDown(const GLTexture &map);

    virtual void draw(Shader *shader);
    
    virtual bool containsPoint(const float &x, const float &y) = 0;
    
private:
    
    void setColourDownBit();
    void setColourUpBit();
    
};

#endif /* _GUISHAPE_H */
