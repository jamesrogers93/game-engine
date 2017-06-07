#include "Core/Engine/Engine.h"

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
