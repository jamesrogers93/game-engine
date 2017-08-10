#include "game-engine/Modules/GUI/GUIProgressBar.h"

#include "game-engine/Modules/GUI/GUIRectangle.h"

GUIProgressBar::GUIProgressBar(const std::string &name, const glm::vec2 &bounds, const glm::vec2 &position) : GUIProperty(name), progression(0.0f), reverse(false)
{
    
    GUIRectangle *guiRectangle1 = new GUIRectangle(bounds);
    guiRectangle1->translateOW(position);
    addShape(guiRectangle1);
    
    GUIRectangle *guiRectangle2 = new GUIRectangle(bounds);
    glm::vec2 p = position;
    p.x -= bounds.x;
    guiRectangle2->translateOW(p);
    guiRectangle2->scaleOW(glm::vec2(0.0, 1.0));
    addShape(guiRectangle2);
}

void GUIProgressBar::setColourUp(const glm::vec4 &colourA, const glm::vec4 &colourB)
{
    shapes[0]->setColourUp(colourA);
    shapes[1]->setColourUp(colourB);
}

void GUIProgressBar::setColourDown(const glm::vec4 &colourA, const glm::vec4 &colourB)
{
    shapes[0]->setColourDown(colourA);
    shapes[1]->setColourDown(colourB);
}

void GUIProgressBar::setProgression(const float &progression)
{
    this->progression = progression;
    
    // Now we need to translate and scale shape[1] accordinginly
    
    GUIRectangle *backRect = (GUIRectangle*)shapes[0];
    
    float Tx;
    
    if(reverse)
    {
        Tx = (backRect->P.x + (backRect->bounds.x * 0.5f)) - ( (backRect->bounds.x * 0.5f) * progression);
    }
    else
    {
        Tx = (backRect->P.x - (backRect->bounds.x * 0.5f)) + ( (backRect->bounds.x * 0.5f) * progression);
    }
    float Sx = progression;
    
    shapes[1]->translateOW(glm::vec2(Tx, backRect->P.y));
    shapes[1]->scaleOW(glm::vec2(Sx, 1.0f));
}

