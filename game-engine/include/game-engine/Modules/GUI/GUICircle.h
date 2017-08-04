#ifndef _GUICIRCLE_H
#define _GUICIRCLE_H

#include "game-engine/Modules/GUI/GUIShape.h"

class GUICircle : public GUIShape
{
public:
    
    float radius;
    
    GUICircle(const float &radius);
    
    void draw(Shader *shader);
    
    bool containsPoint(const float &x, const float &y);
    
private:
    
    static const unsigned int TRIANGLES;
    void initialise();
};

#endif /* _GUICIRCLE_H */
