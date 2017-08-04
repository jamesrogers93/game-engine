#include "game-engine/Modules/GUI/GUIAnalog.h"

#include "game-engine/Modules/GUI/GUICircle.h"

#include "game-engine/Device/System.h"

GUIAnalog::GUIAnalog(const std::string &name, const float &radiusA, const float radiusB, const glm::vec2 position) : GUIProperty(name), drawOnTouched(false)
{
    
    GUIShape *circle = new GUICircle(radiusA);
    circle->translateOW(position);
    addShape(circle);
    
    circle = new GUICircle(radiusB);
    circle->translateOW(position);
    addShape(circle);
    
}

void GUIAnalog::update(Shader *shader)
{
    if(drawOnTouched && !hasTouchDown)
    {
        return;
    }
    
    for(auto shape : shapes)
    {
        shape->draw(shader);
    }
}

void GUIAnalog::setColour(const glm::vec4 &colourA, const glm::vec4 &colourB)
{
    shapes[0]->setColour(colourA);
    shapes[1]->setColour(colourB);
}

void GUIAnalog::setDrawOnTouched(const float &left, const float &right, const float &top, const float &bottom)
{
    drawOnTouched = true;
    this->left = left;
    this->right = right;
    this->top = top;
    this->bottom = bottom;
}

void GUIAnalog::touchDown(const float &x, const float &y)
{
    // If draw on touched. Then we check to see if the point lies within the bounds
    if(drawOnTouched)
    {
        if(x > left && x < right &&
           y > bottom && y < top)
        {
            shapes[0]->translateOW(glm::vec2(x, y));
            shapes[1]->translateOW(glm::vec2(x, y));
            hasTouchDown = true;
        }
        else
        {
            hasTouchDown = false;
        }
    }
    
    // Else we check to see if the point lines in the small circle
    else if(shapes[0]->containsPoint(x, y))
    {
        hasTouchDown = true;
    }
    else
    {
        hasTouchDown = false;
    }
}

void GUIAnalog::touchMove(const float &x, const float &y)
{
    if(hasTouchDown)
    {
        glm::vec2 touchPoint(x, y);
        
        glm::vec2 direction = shapes[0]->position - touchPoint;
        
        float length = glm::length(direction);
        
        GUICircle *circle = (GUICircle*)shapes[0];
        if((length * length) > (circle->radius * circle->radius))
        {
            shapes[1]->translateOW(circle->position - (glm::normalize(direction) * circle->radius));
        }
        else
        {
            shapes[1]->translateOW(glm::vec2(x, y));
        }
        hasTouchMove = true;
    }
    else
    {
        hasTouchMove = false;
    }
}

void GUIAnalog::touchUp(const float &x, const float &y)
{
    if(hasTouchDown)
    {
        hasTouchUp = true;
        hasTouchDown = false;
        
        shapes[1]->translateOW(shapes[0]->position);
    }
    else
    {
        hasTouchUp = false;
        hasTouchDown = false;
    }
}

glm::vec2 GUIAnalog::getOffset()
{
    if(hasTouchMove)
    {
        glm::vec3 position1Norm;
        glm::vec3 position2Norm;
        
        position1Norm.x = position1Norm.x / (float)System::screenWidth;
        position2Norm.x = position2Norm.x / (float)System::screenWidth;
        
        position1Norm.y = position1Norm.y / (float)System::screenHeight;
        position2Norm.y = position2Norm.y / (float)System::screenHeight;
        
        return position1Norm - position2Norm;
    }
    
    return glm::vec2(0.0);
}
