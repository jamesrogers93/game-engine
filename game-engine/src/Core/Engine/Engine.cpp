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
    CoreModule* mPtr = this->modules.at(module->getType());
    
    if(mPtr == NULL)
    {
        this->modules[module->getType()] = module;
        return true;
    }
    
	return false;
}

bool Engine::removeCoreModule(const CoreModuleType &module)
{
    CoreModule* mPtr = this->modules.at(module);
    
    if(mPtr != NULL)
    {
        this->modules.erase(module);
        return true;
    }
    
	return false;
}

template<typename T>
const T* Engine::getCoreModule(const CoreModuleType &module)
{

	T* mPtr = static_cast<T>(this->modules.at(module));

	if (mPtr == NULL)
		return NULL;
	else
		return mPtr;

}

void Engine::updateAll()
{
    // MUST IMPLEMENT
}

void Engine::updateIncluding(const std::vector<CoreModuleType> modules)
{
    // MUST IMPLEMENT
}

void Engine::updateExcluding(const std::vector<CoreModuleType> modules)
{
    // MUST IMPLEMENT
}

