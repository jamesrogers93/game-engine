#ifndef _GUIRECTANGLE_H
#define _GUIRECTANGLE_H

#include "game-engine/Modules/GUI/GUIShape.h"

class GUIRectangle : public GUIShape
{
public:
    
    glm::vec2 bounds;
    
    GUIRectangle(const glm::vec2 &bounds);
    
    void draw(Shader *shader);
    
private:
    
    void initialise();
};

#endif /* _GUIRECTANGLE_H */
