#include "game-engine/Core/Engine/Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

bool Engine::addCoreModule(CoreModule *)
{
	return false;
}

bool Engine::removeCoreModule(CoreModule *)
{
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

