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
    
    glm::vec2 P;
    glm::vec2 S;
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
    
    
    GUIShape() : P(glm::vec2(0.0f)), S(glm::vec2(1.0f)), colourUpSet(false), colourDownSet(false), colourMapUpSet(false), colourMapDownSet(false), colourUpBitwise(0), colourDownBitwise(0), isDown(false)
    {}
    
    void translateOW(const glm::vec2 &position) { this->P = position; }
    void translate(const glm::vec2 &position) { this->P += position; }
    void scaleOW(const glm::vec2 &scale) { this->S = scale; }
    void scale(const glm::vec2 &scale) { this->S += scale; }
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
