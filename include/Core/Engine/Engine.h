#ifndef _ENGINE_H
#define _ENGINE_H

// STL
#include <map>

// Engine
#include "Core/Scene/SceneManager.h"
#include "Core/Modules/CoreModule.h"

//class CoreModule;
//enum CoreModuleType;

class Engine
{
public:

	static Engine& getInstance()
	{
		static Engine engine;

		return engine;
	}

	bool addCoreModule(CoreModule* module);
	bool removeCoreModule(CoreModule* module);

	template<typename T>
	const T* getCoreModule(const CoreModuleType &module);

private:
	Engine();
	~Engine();

	SceneManager* sceneManager;
	std::map<CoreModuleType, CoreModule*> modules;

};

#endif /* _ENGINE_H */
