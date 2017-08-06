#ifndef _GUIANALOG_H
#define _GUIANALOG_H

#include "game-engine/Modules/GUI/GUIProperty.h"

// GLM
#include <glm/glm.hpp>

class GUIAnalog : public GUIProperty
{
public:
    
    GUIAnalog(const std::string &name, const float &radiusA, const float radiusB, const glm::vec2 position = glm::vec2(0.0));
    
    void setColourUp(const glm::vec4 &colourA, const glm::vec4 &colourB);
    void setColourDown(const glm::vec4 &colourA, const glm::vec4 &colourB);
    void setDrawOnTouched(const float &left, const float &right, const float &top, const float &bottom);
    
    void update(Shader *shader);
    
    glm::vec2 getOffset();
    
    void touchDown(const float &x, const float &y);
    void touchMove(const float &x, const float &y);
    void touchUp(const float &x, const float &y);
    
private:
    
    glm::vec2 position;
    bool drawOnTouched;
    
    float left, right, top, bottom;
};

#endif /* _GUIANALOG_H */
