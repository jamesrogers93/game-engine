#ifndef _ENGINE_H
#define _ENGINE_H

// STL
#include <map>
#include <vector>

// Engine
#include "game-engine/Modules/CoreModule.h"
#include "game-engine/Core/Dispatch/DispatchQueue.h"

class SceneManager;

class Engine
{
public:

	static Engine& getInstance()
	{
		static Engine engine;

		return engine;
	}
    
	bool addCoreModule(CoreModule* module);
	bool removeCoreModule(const CoreModuleType &module);

	//template<typename T>
    //T* getCoreModule(const CoreModuleType &module);
    CoreModule* getCoreModule(const CoreModuleType &module);
    
    void update(const CoreModuleType &module, const bool &dispatch = false);
    //void updateAll();
    //void updateIncluding(const std::vector<CoreModuleType> modules);
    //void updateExcluding(const std::vector<CoreModuleType> modules);

private:
	Engine();
	~Engine();

	SceneManager *sceneManager;
	std::map<CoreModuleType, CoreModule*> modules;
    
    DispatchQueue mDispatchQueue;

};

#endif /* _ENGINE_H */
