#include "game-engine/Core/Scene/Scene.h"
#include "game-engine/Core/Entity/ENode.h"

const std::string & Scene::getName()
{
	return this->name;
}

void Scene::update()
{
    
    for(auto &entity : this->entities)
    {
        entity->updateGlobalModel();
        entity->updateChildren();
        entity->update();
    }
}
