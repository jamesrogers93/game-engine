#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

// STL
#include <map>
#include <string>

// Engine
class Scene;

class SceneManager
{
public:

	static SceneManager& getInstance()
	{
		static SceneManager instance;

		return instance;
	}

	bool addScene(Scene* scene);
	bool removeScene(Scene* scene);
	Scene* getScene(std::string name);

	void update();

private:
	SceneManager();
	~SceneManager();

	std::string activeScene;
	std::map<std::string, Scene*> scenes;
};

#endif /* _SCENEMANAGER_H */
