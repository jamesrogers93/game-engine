#include "game-engine/Core/Scene/SceneManager.h"
#include "game-engine/Core/Scene/Scene.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

bool SceneManager::addScene(Scene *scene)
{
    
    if(this->scenes.find(scene->getName()) != this->scenes.end())
    {
        return false;
        
    } else
    {
        scene->initalise();
        this->scenes[scene->getName()] = scene;
        return true;
    }
}

bool SceneManager::removeScene(Scene *scene)
{
    
    if(this->scenes.find(scene->getName()) != this->scenes.end())
    {
        scene->deinitalise();
        this->scenes.erase(scene->getName());
        return true;
        
    } else
    {
        return false;
    }
}

Scene* SceneManager::getScene(const std::string &name)
{
    
    if(this->scenes.find(name) != this->scenes.end())
    {
        return this->scenes.at(name);
        
    } else
    {
        return NULL;
    }
}

bool SceneManager::makeActiveScene(const std::string &name)
{
    if(this->scenes.find(name) != this->scenes.end())
    {
        this->activeScene = name;
        return true;
        
    } else
    {
        return false;
    }
}

void SceneManager::update()
{
    if(this->scenes.find(this->activeScene) != this->scenes.end())
    {
        //this->scenes.at(this->activeScene)->update();
    
    } else
    {
            // LOG
    }
}


