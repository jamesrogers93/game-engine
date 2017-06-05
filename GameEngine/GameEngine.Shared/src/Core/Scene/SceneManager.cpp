#include "Core/Scene/SceneManager.h"
#include "Core/Scene/Scene.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

bool SceneManager::addScene(Scene *scene)
{
	Scene *sPtr = this->scenes.at(scene->getName());

	if (sPtr == NULL)
	{
		this->scenes[scene->getName()] = scene;
		return true;
	}

	return false;
}

bool SceneManager::removeScene(Scene * scene)
{
	Scene *sPtr = this->scenes.at(scene->getName());

	if (sPtr != NULL)
	{
		sPtr->deinitalise();
		this->scenes.erase(sPtr->getName());
		return true;
	}
	
	return false;
}

Scene * SceneManager::getScene(std::string name)
{
	Scene *sPtr = this->scenes.at(name);

	if (sPtr != NULL)
	{
		// LOG
	}

	return sPtr;
}

void SceneManager::update()
{
	Scene *sPtr = this->scenes.at(this->activeScene);

	if (sPtr == NULL)
	{
		// LOG
	}
	else
	{
		sPtr->update();
	}
}


