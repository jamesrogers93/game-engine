#include "game-engine/Core/Scene/Scene.h"
#include "game-engine/Core/Entity/ENode.h"

const std::string & Scene::getName()
{
	return this->name;
}

void Scene::initalise()
{
    // Go through all the nodes and attach them to the engine
    
    const size_t numEntites = this->entities.size();
    for(unsigned int i = 0; i < numEntites; i++)
    {
        this->entities[i]->attachToEngine();
    }
}

void Scene::update()
{
    
    for(auto &entity : this->entities)
    {
        entity->updateGlobalModel();
    }
}
