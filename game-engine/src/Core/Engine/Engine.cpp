#include "game-engine/Core/Engine/Engine.h"

// Engine
#include "game-engine/Core/Scene/SceneManager.h"

Engine::Engine()
{
    this->sceneManager = &SceneManager::getInstance();
}

Engine::~Engine()
{
}

bool Engine::addCoreModule(CoreModule *module)
{
    if ( this->modules.find(module->getType()) != this->modules.end() )
    {
        // found
        return false;
        
    } else
    {
        // not found
        this->modules[module->getType()] = module;
        return true;
    }
}

bool Engine::removeCoreModule(const CoreModuleType &module)
{
    if ( this->modules.find(module) != this->modules.end() )
    {
        // found
        this->modules.erase(module);
        return true;
        
    } else
    {
        // not found
        return false;
    }
}

/*template<typename T>
T* Engine::getCoreModule(const CoreModuleType &module)
{

 // CHANGE map.at TO map.find
	T* mPtr = static_cast<T*>(this->modules.at(module));

	if (mPtr == NULL)
		return NULL;
	else
		return mPtr;

}*/

CoreModule* Engine::getCoreModule(const CoreModuleType &module)
{
    if ( this->modules.find(module) != this->modules.end() )
    {
        // found
        return this->modules.at(module);
        
    } else
    {
        // not found
        return NULL;
    }
}

void Engine::updateAll()
{
    for(auto const &module : this->modules)
    {
        module.second->update();
    }
}

void Engine::updateIncluding(const std::vector<CoreModuleType> modules)
{
    for(auto const &module : modules)
    {
        if(this->modules.find(module) != this->modules.end())
        {
            this->modules.at(module)->update();
        }
    }
}

void Engine::updateExcluding(const std::vector<CoreModuleType> modules)
{
    // MUST IMPLEMENT
}

