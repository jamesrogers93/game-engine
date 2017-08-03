#include "game-engine/Modules/GUI/GUIProperty.h"
#include "game-engine/Modules/GUI/GUI.h"

#include "game-engine/Defines/OpenGL.h"

#include "game-engine/Modules/Graphics/Shader.h"

// GLM
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TEST
#include "game-engine/Modules/GUI/GUIRectangle.h"
#include "game-engine/Modules/GUI/GUICircle.h"
// END TEST

#include "game-engine/Device/System.h"

GUIProperty::GUIProperty(const std::string &name) : Property(name, Property::GUI)
{
    GUIShape *rect = new GUIRectangle(glm::vec2(200.0f, 200.0f));
    rect->translateOW(glm::vec2(400.0f, 400.0f));
    rect->setColour(glm::vec4(1.0, 0.0, 0.0, 1.0));
    shapes.push_back(rect);
    
    
    GUIShape *circle = new GUICircle(100.0f);
    circle->translateOW(glm::vec2(1000.0f, 400.0f));
    circle->setColour(glm::vec4(0.0, 1.0, 0.0, 1.0));
    shapes.push_back(circle);

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
