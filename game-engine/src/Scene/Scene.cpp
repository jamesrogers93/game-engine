#include "game-engine/Scene/Scene.h"
#include "game-engine/Scene/SceneLogic.h"
#include "game-engine/Entity/Entity.h"
#include "game-engine/Entity/Property.h"

#include <iostream>

const std::string & Scene::getName()
{
	return this->name;
}

void Scene::removeEntity(const std::string &name)
{
    for(unsigned int i = 0; i < this->entities.size(); i++)
    {
        if(name == entities[i]->getName())
        {
            entities[i]->deinitialise();
            entities.erase(entities.begin() + i);
        }
    }
}

Entity* Scene::getEntity(const std::string &name)
{
    for(unsigned int i = 0; i < this->entities.size(); i++)
    {
        if(name == entities[i]->getName())
        {
            return entities[i];
        }
    }
    
    return NULL;
}

void Scene::prepare()
{
    if(!mHasPrepared)
    {
        for(unsigned int i = 0; i < this->entities.size(); i++)
        {
            prepare(this->entities[i]);
        }
        
        mHasPrepared = true;
    }
    else
    {
        std::cout << "Scene already prepared." << std::endl;
    }
}

void Scene::unPrepare()
{
    if(mHasPrepared)
    {
        for(unsigned int i = 0; i < this->entities.size(); i++)
        {
            unPrepare(this->entities[i]);
        }
    
        mHasPrepared = false;
    }
    else
    {
        std::cout << "Scene already unprepared." << std::endl;
    }
}

void Scene::prepare(Entity *entity)
{
    // Prepare transformations
    entity->updateGlobalModel();
    
    for(unsigned int i = 0; i < entity->getProperties().size(); i++)
    {
        if(!entity->getProperties()[i]->makeActive())
        {
            std::cout << "Could not active property: " << entity->getProperties()[i]->getName() << std::endl;
        }
    }
    
    for(unsigned int i = 0; i < entity->getChildren().size(); i++)
    {
        prepare(entity->getChildren()[i]);
    }
}

void Scene::unPrepare(Entity *entity)
{
    for(unsigned int i = 0; i < entity->getProperties().size(); i++)
    {
        if(!entity->getProperties()[i]->makeUnactive())
        {
            std::cout << "Could not deactivate property: " << entity->getProperties()[i]->getName() << std::endl;
        }
    }
    
    for(unsigned int i = 0; i < entity->getChildren().size(); i++)
    {
        unPrepare(entity->getChildren()[i]);
    }
}

void Scene::update()
{
    
    for(auto &entity : this->entities)
    {
        //entity->updateGlobalModel();
        entity->update();
    }
    
    if(mSceneLogic != NULL)
    {
        mSceneLogic->update();
    }
}

void Scene::draw()
{
    if(mSceneLogic != NULL)
    {
        mSceneLogic->draw();
    }
}
