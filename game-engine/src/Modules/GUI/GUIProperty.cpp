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


void GUIProperty::setCallBack( std::function<void()> functionPtr, const bool &callbackOnTouchDown,  const bool &callbackOnTouchMove,  const bool &callbackOnTouchUp)
{
    this->functionPtr = functionPtr;
    this->callbackOnTouchDown = callbackOnTouchDown;
    this->callbackOnTouchMove = callbackOnTouchMove;
    this->callbackOnTouchUp = callbackOnTouchUp;
}

void GUIProperty::touchDown(const float &x, const float &y)
{
    // Loop over shapes to see if the point touches them
    
    for(auto *shape : shapes)
    {
        if(shape->containsPoint(x, y))
        {
            hasTouchDown = true;
            shape->isDown = true;
        }
    }
    
    if(hasTouchDown && callbackOnTouchDown)
    {
        functionPtr();
    }
}

void GUIProperty::touchMove(const float &x, const float &y)
{
    // Loop over shapes to see if the point still touches them
    if(hasTouchDown)
    {
        hasTouchMove = true;
        
        if(callbackOnTouchMove)
        {
            functionPtr();
        }
    }
}

void GUIProperty::touchUp(const float &x, const float &y)
{
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
            hasTouchUp = true;
        }
        else
        {
            hasTouchUp = false;
        }
        
        hasTouchDown = false;
        hasTouchMove = false;
    }
    else
    {
        hasTouchUp = false;
        hasTouchDown = false;
        hasTouchMove = false;
    }
    
    for(auto *shape : shapes)
    {
        shape->isDown = false;
    }
    
    if(hasTouchUp && callbackOnTouchUp)
    {
        functionPtr();
    }
}
