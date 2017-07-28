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
	Scene* getScene(const std::string &name);
    bool makeActiveScene(const std::string &name);

	void update();
    void draw();

private:
	SceneManager();
	~SceneManager();

	//std::string activeScene;
    Scene* activeScene;
	std::map<std::string, Scene*> scenes;
};

#endif /* _SCENEMANAGER_H */
