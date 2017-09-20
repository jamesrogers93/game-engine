#include "game-engine/Core/Main/SceneManager.h"
#include "game-engine/Core/Main/Scene.h"

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
        //scene->initialise();
        this->scenes[scene->getName()] = scene;
        return true;
    }
}

bool SceneManager::removeScene(Scene *scene)
{
    
    if(this->scenes.find(scene->getName()) != this->scenes.end())
    {
        scene->unPrepare();
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
    // Unprepare active scene
    if(activeScene != NULL)
    {
        activeScene->unPrepare();
    }
    
    //if(this->scenes.find(this->activeScene) != this->scenes.end())
    //{
    //    this->scenes[this->activeScene]->unPrepare();
    //}
    
    // If the scene exists, make it active and prepare it.
    if(this->scenes.find(name) != this->scenes.end())
    {
        activeScene = scenes.at(name);
        activeScene->prepare();
        
        //this->activeScene = name;
        //this->scenes[this->activeScene]->prepare();
        return true;
        
    } else
    {
        return false;
    }
}

//#include <thread>
void SceneManager::update()
{
    if(activeScene != NULL)
    {
        activeScene->update();
    }
    else
    {
        // LOG
    }
}

void SceneManager::draw()
{
    if(activeScene != NULL)
    {
        activeScene->draw();
    }
    else
    {
        // LOG
    }
}


