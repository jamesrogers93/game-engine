#include "game-engine/Core/Modules/AR/AR.h"

// Game Engine Device
#include "game-engine/Core/Device/CameraCapture.h"

AR::AR() : CoreModule(CM_AR)
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

bool AR::update()
{
    
    if(this->arEntities.find(this->activeAREntity) != this->arEntities.end())
    {
        this->arEntities[this->activeAREntity]->draw();
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
        this->activeAREntity = nameLow;
        return true;
    }
    
    return false;
}
