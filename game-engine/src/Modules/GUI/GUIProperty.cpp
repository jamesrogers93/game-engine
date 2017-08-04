#include "game-engine/Modules/GUI/GUIProperty.h"
#include "game-engine/Modules/GUI/GUI.h"

#include "game-engine/Modules/Graphics/Shader.h"


GUIProperty::GUIProperty(const std::string &name) : Property(name, Property::GUI), hasTouchDown(false), hasTouchMove(false), hasTouchUp(false)
{

}

void GUIProperty::update(Shader *shader)
{
    
    for(auto shape : shapes)
    {
        shape->draw(shader);
    }
}

bool GUIProperty::makeActive()
{
    return GUI::getInstance().addGUIProperty(this->getName(), this);
}

bool GUIProperty::makeUnactive()
{
    return GUI::getInstance().removeGUIProperty(this->getName());
}

void GUIProperty::touchDown(const float &x, const float &y)
{
    // Loop over shapes to see if the point touches them
    
    for(auto *shape : shapes)
    {
        if(shape->containsPoint(x, y))
        {
            hasTouchDown = true;
            return;
        }
    }
}

void GUIProperty::touchMove(const float &x, const float &y)
{
    // Loop over shapes to see if the point still touches them
    if(hasTouchDown)
    {
        bool stillTouched = false;
        for(auto *shape : shapes)
        {
            if(shape->containsPoint(x, y))
            {
                stillTouched = true;
            }
        }
        
        if(stillTouched)
        {
            hasTouchMove = true;
        }
        else
        {
            hasTouchDown = false;
        }
    }
}

void GUIProperty::touchUp(const float &x, const float &y)
{
    if(hasTouchDown)
    {
        hasTouchUp = true;
        hasTouchDown = false;
    }
    else
    {
        hasTouchUp = false;
        hasTouchDown = false;
    }
}
