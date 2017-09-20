#include "game-engine/Modules/AR/AR.h"

// Game Engine Device
#include "game-engine/Peripherals/CameraCapture.h"

#include "game-engine/Core/Utilities/StringUtil.h"

AR::AR() : CoreModule(CoreModuleType::CM_AR)
{
    
}

bool AR::initialise()
{
    return true;
}

bool AR::deinitialise()
{
    return true;
}

// Game Engine Core
#include "game-engine/Core/GL/GLThread.h"

bool AR::update()
{
    
    if(activeAREntity != NULL)
    {
        // Commented out because the camera is being drawn on the opengl thread inside it's method
        //GLThread::getInstance().giveJob(std::bind(&AREntity::draw, activeEntity));
        
        activeAREntity->draw();
    }
    
    return true;
}

bool AR::addAREntity(const std::string &name, AREntity *entity)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
    if(this->arEntities.find(nameLow) != this->arEntities.end())
    {
        return false;
    }
    else
    {
        this->arEntities[nameLow] = entity;
        return true;
    }
}

bool AR::removeAREntity(const std::string &name)
{
    std::string nameLow = toLower(name);
    
    auto it = arEntities.find(nameLow);
    
    if(it != arEntities.end())
    {
        if(name == it->second->getName())
        {
            activeAREntity = NULL;
        }
        // remove
        arEntities.erase(it);
        
        return true;
    }
    else
    {
        return false;
    }
    
}

bool AR::setActiveAREntity(const std::string &name)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
    if(this->arEntities.find(nameLow) != this->arEntities.end())
    {
        this->activeAREntity = this->arEntities.at(nameLow);
        return true;
    }
    
    return false;
}
