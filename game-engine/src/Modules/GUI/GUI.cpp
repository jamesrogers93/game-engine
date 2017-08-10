#include "game-engine/Modules/GUI/GUI.h"

#include "game-engine/Modules/Graphics/Shader.h"

#include "game-engine/Util/StringUtil.h"

#include "game-engine/Device/System.h"

// GLM
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "game-engine/Defines/OpenGL.h"


const std::string vertex =
"#version 300 es\n"
"\n"
"// In variables\n"
"in vec3 position;\n"
"in vec2 uv0;\n"
"\n"
"// Out variables\n"
"out mediump vec2 UV0;\n"
"\n"
"uniform mat4 projection;\n"
"uniform mediump vec2 translation;\n"
"uniform mediump vec2 scale;\n"
"\n"
"void main()\n"
"{\n"
"    UV0 = uv0;\n"
"\n"
"    gl_Position = projection * (vec4(translation, 0.0, 1.0) + ( vec4(scale, 0.0f, 1.0f) * vec4(position, 1.0)));\n"
"}\n";

const std::string fragment =
"#version 300 es\n"
"\n"
"// Constants \n"
"const int COLOUR_BIT     = 0x01;\n"
"const int COLOUR_MAP_BIT = 0x02;\n"
"\n"
"// In variables\n"
"in mediump vec2 UV0;\n"
"\n"
"// Out variables\n"
"out mediump vec4 Colour;\n"
"\n"
"// Uniform variables\n"
"uniform mediump vec4 colour;\n"
"uniform sampler2D colour_map;\n"
"uniform int colour_bit; \n"
"\n"
"void main()\n"
"{\n"
"   Colour = vec4(0.0);\n"
"   if((colour_bit & COLOUR_BIT) == COLOUR_BIT)\n"
"   {\n"
"       Colour += colour;\n"
"   }\n"
"\n"
"   if((colour_bit & COLOUR_MAP_BIT) == COLOUR_MAP_BIT)\n"
"   {\n"
"       Colour += texture(colour_map, UV0);\n"
"   }\n"
"}\n";

GUI::GUI() : CoreModule(CoreModuleType::CM_GUI){}

bool GUI::initialise()
{
    
    std::vector<std::pair<GLint, std::string> > vertexAttribs;
    vertexAttribs.push_back(std::make_pair(ATTRIB_POSITION, "position"));
    vertexAttribs.push_back(std::make_pair(ATTRIB_UV0, "uv0"));
    
    std::vector<std::string> uniformNames;
    uniformNames.push_back("projection");
    uniformNames.push_back("translation");
    uniformNames.push_back("scale");
    uniformNames.push_back("colour");
    uniformNames.push_back("colour_map");
    uniformNames.push_back("colour_bit");
    
    shader = Shader::loadShaderFromString(vertex, fragment, vertexAttribs, uniformNames);
    
    float screenWidth = (float)System::screenWidth;
    float screenHeight = (float)System::screenHeight;
    projection = glm::ortho(0.0f, screenWidth*0.5f, 0.0f, screenHeight*0.5f); // Dont know why half
    
    return true;
}

bool GUI::deinitialise()
{
    return true;
}

bool GUI::update()
{
    
    glDisable(GL_DEPTH_TEST);
    
    shader->use();
    
    const GLint *loc = shader->getUniformLocation("projection");
    if(loc != NULL)
    {
        glUniformMatrix4fv(*loc, 1, false, glm::value_ptr(projection));
    }
    
    // Draw all gui properties to the screen
    for(auto &guiProperty : guiProperties)
    {
        guiProperty.second->update(shader);
    }
    
    glEnable(GL_DEPTH_TEST);
    
    return true;
}

void GUI::touchDown(const float &x, const float &y)
{
    for(auto &prop : guiProperties)
    {
        if(prop.second->isTouchable)
        {
            prop.second->touchDown(x, y);
        }
    }
}

void GUI::touchMove(const float &x, const float &y)
{
    for(auto &prop : guiProperties)
    {
        if(prop.second->isTouchable)
        {
            prop.second->touchMove(x, y);
        }
    }
}

void GUI::touchUp(const float &x, const float &y)
{
    for(auto const &prop : guiProperties)
    {
        if(prop.second->isTouchable)
        {
            prop.second->touchUp(x, y);
        }
    }
}

bool GUI::addGUIProperty(const std::string &name, GUIProperty* guiProperty)
{
    
    // Make name lower case
    std::string nameLow = toLower(name);
    
    auto it = guiProperties.find(nameLow);
    
    if(it == guiProperties.end())
    {
        guiProperties[nameLow] = guiProperty;
        return true;
    }
    else
    {
        return false;
    }
}

bool GUI::removeGUIProperty(const std::string &name)
{
    // Make name lower case
    std::string nameLow = toLower(name);
    
    auto it = guiProperties.find(nameLow);
    
    if(it != guiProperties.end())
    {
        guiProperties.erase(it);
        return true;
    }
    else
    {
        return false;
    }
}

GUIProperty* GUI::getGUIProperty(const std::string &name)
{
    auto it = guiProperties.find(name);
    
    if(it != guiProperties.end())
    {
        return it->second;
    }
    else
    {
        return NULL;
    }
}
