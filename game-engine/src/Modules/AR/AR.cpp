#include "game-engine/Modules/AR/AR.h"

// Game Engine Device
#include "game-engine/Device/CameraCapture.h"

AR::AR() : CoreModule(CoreModuleType::CM_AR)
{
    
}

bool AR::initalise()
{
    return true;
}

bool AR::deinitalise()
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
