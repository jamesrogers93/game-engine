#ifndef _GUI_H
#define _GUI_H

// STD
#include <string>
#include <unordered_map>

// Game Engine
#include "game-engine/Modules/CoreModule.h"

#include "game-engine/Modules/GUI/GUIProperty.h"

// GLM
#include <glm/glm.hpp>

class Shader;

class GUI : public CoreModule
{
public:
    
    static GUI& getInstance()
    {
        static GUI instance;
        return instance;
    }
    
    bool initialise();
    bool deinitialise();
    bool update();
    
    void touchDown(const float &x, const float &y);
    void touchMove(const float &x, const float &y);
    void touchUp(const float &x, const float &y);
    
    bool addGUIProperty(const std::string &name, GUIProperty* guiProperty);
    bool removeGUIProperty(const std::string &name);
    GUIProperty* getGUIProperty(const std::string &name);

private:
    
    Shader *shader;
    glm::mat4 projection;
    std::unordered_map<std::string, GUIProperty*> guiProperties;
    
    GUI();
    GUI(GUI const&);              // Don't Implement
    void operator=(GUI const&);		// Don't implement
    
};

#endif /* _GUI_H */
