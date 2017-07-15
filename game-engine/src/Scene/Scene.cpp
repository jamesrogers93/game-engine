#include "game-engine/Scene/Scene.h"
#include "game-engine/Entity/Entity.h"

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
