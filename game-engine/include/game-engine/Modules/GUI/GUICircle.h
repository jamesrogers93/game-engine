#ifndef _GUICIRCLE_H
#define _GUICIRCLE_H

#include "game-engine/Modules/GUI/GUIShape.h"

class GUICircle : public GUIShape
{
public:
    
    float radius;
    
    GUICircle(const float &radius);
    
    void draw(Shader *shader);
    
private:
    
    static const unsigned int TRIANGLES;
    void initialise();
};

#endif /* _GUICIRCLE_H */
