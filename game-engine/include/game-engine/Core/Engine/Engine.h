#ifndef _ENGINE_H
#define _ENGINE_H

// STL
#include <map>
#include <vector>

// Engine
#include "game-engine/Core/Scene/SceneManager.h"
#include "game-engine/Core/Modules/CoreModule.h"

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
    
    void updateAll();
    void updateIncluding(const std::vector<CoreModuleType> modules);
    void updateExcluding(const std::vector<CoreModuleType> modules);

private:
	Engine();
	~Engine();

	SceneManager *sceneManager;
	std::map<CoreModuleType, CoreModule*> modules;

};

#endif /* _ENGINE_H */
