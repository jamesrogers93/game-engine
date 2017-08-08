#ifndef _GUIPROGRESSBAR_H
#define _GUIPROGRESSBAR_H

#include "game-engine/Modules/GUI/GUIProperty.h"

// GLM
#include <glm/glm.hpp>

class GUIProgressBar : public GUIProperty
{
public:
    
    GUIProgressBar(const std::string &name, const glm::vec2 &bounds, const glm::vec2 &position);
    
    void setColourUp(const glm::vec4 &colourA, const glm::vec4 &colourB);
    void setColourDown(const glm::vec4 &colourA, const glm::vec4 &colourB);
    
    void setProgression(const float &progression);
    
private:
    
    glm::vec2 position;
    
    float progression;
};

#endif /* _GUIPROGRESSBAR_H */
