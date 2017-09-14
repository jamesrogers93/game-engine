#include "game-engine/Modules/AI/AI.h"
#include "game-engine/Modules/AI/AIFSM.h"
#include "game-engine/Modules/AI/AIDT.h"

AI::AI() : CoreModule(CoreModuleType::CM_AI)
{

}

bool AI::initialise()
{
    return false;
}

bool AI::deinitialise()
{
    return false;
}

bool AI::update()
{
    
    for(auto fsm : fsms)
    {
        fsm.second->update();
    }
    
    for(auto dt : dts)
    {
        dt.second->update();
    }
    
    return true;
}

bool AI::addFSMProperty(const std::string &name, AIFSM *property)
{
    auto it = fsms.find(name);
    
    if(it == fsms.end())
    {
        fsms[name] = property;
        return true;
    }
    
    return false;
}

bool AI::addDTProperty(const std::string &name, AIDT *property)
{
    auto it = dts.find(name);
    
    if(it == dts.end())
    {
        dts[name] = property;
        return true;
    }
    
    return false;
}

bool AI::removeFSMProperty(const std::string &name)
{
    auto it = fsms.find(name);
    
    if(it != fsms.end())
    {
        fsms.erase(it);
        return true;
    }
    
    return false;
}

bool AI::removeDTProperty(const std::string &name)
{
    auto it = dts.find(name);
    
    if(it != dts.end())
    {
        dts.erase(it);
        return true;
    }
    
    return false;
}
