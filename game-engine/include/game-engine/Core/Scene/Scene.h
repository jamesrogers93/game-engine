#ifndef _SCENE_H
#define _SCENE_H

#include <string>

#include "game-engine/Core/Entity/ENode.h"

class Scene
{
public:

	virtual void initalise() = 0;
	virtual void deinitalise() = 0;
	virtual std::string update() = 0;

	const std::string& getName();

protected:
	Scene(std::string name) : name(name) {}
	~Scene() {}

private:
	std::string name;
};

#endif /* _SCENE_H */
