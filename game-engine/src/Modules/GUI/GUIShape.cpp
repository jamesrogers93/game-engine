#include "game-engine/Modules/GUI/GUIShape.h"

// GLM
#include <glm/gtc/type_ptr.hpp>

void GUIShape::draw(Shader *shader)
{
    const GLint *loc = shader->getUniformLocation("translation");
    glUniform2fv(*loc, 1, glm::value_ptr(position));
    
    loc = shader->getUniformLocation("Colour");
    if(isDown)
    {
        glUniform4fv(*loc, 1, glm::value_ptr(colourDown));
    }
    else
    {
        glUniform4fv(*loc, 1, glm::value_ptr(colourUp));
    }
    
    mesh->draw();
}
