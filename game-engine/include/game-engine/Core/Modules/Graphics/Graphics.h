#pragma once

// STD
#include <string>
#include <map>

// Game Engine
#include "game-engine/Core/Modules/CoreModule.h"

class Geometry;
class Shader;

class Graphics : public CoreModule
{
public:
	static Graphics& getInstance()
	{
		static Graphics    instance;
		return instance;
	}

	bool initalise();
	bool deinitalise();

	bool draw(const std::string &name);

	bool addGeometry(std::string name, Geometry *geometry);
	bool addShader(std::string name, Shader *shader);

	const Shader* getShader(std::string name);

private:
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Geometry*> geometry;
	//std::map<std::string, GLuint> textures;

	Graphics() : CoreModule(CMT_GRAPHICS){}
	Graphics(Graphics const&);              // Don't Implement
	void operator=(Graphics const&);		// Don't implement
};
