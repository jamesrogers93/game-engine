#include "game-engine/Modules/GUI/GUIShape.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

void GUIShape::setColourUp(const glm::vec4 &colour)
{
    this->colourUp = colour;
    colourUpSet = true;
    setColourUpBit();
}

void GUIShape::setColourDown(const glm::vec4 &colour)
{
    this->colourDown = colour;
    colourDownSet = true;
    setColourDownBit();
}

void GUIShape::setMapUp(const GLTexture &map)
{
    this->colourMapUp = map;
    colourMapUpSet = true;
    setColourUpBit();
}
void GUIShape::setMapDown(const GLTexture &map)
{
    this->colourMapDown = map;
    colourMapDownSet = true;
    setColourDownBit();
}

void GUIShape::draw(Shader *shader)
{
    const GLint *loc = shader->getUniformLocation("translation");
    glUniform2fv(*loc, 1, glm::value_ptr(position));
    
    loc = shader->getUniformLocation("colour_bit");
    
    if(isDown)
    {
        glUniform1i(*loc, colourDownBitwise);
        
        // Texture Map
        if(colourDownBitwise & COLOUR_MAP_BIT)
        {
            loc = shader->getUniformLocation("colour_map");
            glUniform1i(*loc, 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, colourMapDown.getTextureID());
        }
        
        // Colour vector
        if(colourDownBitwise & COLOUR_BIT)
        {
            loc = shader->getUniformLocation("colour");
            glUniform4fv(*loc, 1, glm::value_ptr(colourDown));
        }
    }
    else
    {
        glUniform1i(*loc, colourUpBitwise);
        
        // Texture Map
        if(colourUpBitwise & COLOUR_MAP_BIT)
        {
            loc = shader->getUniformLocation("colour_map");
            glUniform1i(*loc, 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, colourMapUp.getTextureID());
        }
        
        // Colour vector
        if(colourUpBitwise & COLOUR_BIT)
        {
            loc = shader->getUniformLocation("colour");
            glUniform4fv(*loc, 1, glm::value_ptr(colourUp));
        }
    }

    
    
    mesh->draw();
}

void GUIShape::setColourDownBit()
{
    if(colourDownSet && colourMapDownSet)
    {
        colourDownBitwise = COLOUR_BIT | COLOUR_MAP_BIT;
    }
    else if(colourDownSet)
    {
        colourDownBitwise = COLOUR_BIT;
    }
    else if (colourMapDownSet)
    {
        colourDownBitwise = COLOUR_MAP_BIT;
    }
    else
    {
        colourDownBitwise = 0;
    }
}

void GUIShape::setColourUpBit()
{
    if(colourUpSet && colourMapUpSet)
    {
        colourUpBitwise = COLOUR_BIT | COLOUR_MAP_BIT;
    }
    else if(colourUpSet)
    {
        colourUpBitwise = COLOUR_BIT;
    }
    else if (colourMapUpSet)
    {
        colourUpBitwise = COLOUR_MAP_BIT;
    }
    else
    {
        colourUpBitwise = 0;
    }
}
