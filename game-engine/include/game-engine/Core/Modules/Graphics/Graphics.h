#ifndef _GRAPHICS_H
#define _GRAPHICS_H

// STD
#include <string>
#include <map>

// Game Engine
#include "game-engine/Core/Modules/CoreModule.h"

class GeometryEntity;
class Shader;
class Geometry;
class Material;
class Texture;

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
    bool update();

    bool addGeometryEntity(const std::string& name, GeometryEntity* geometryEntity);
    bool addShader(const std::string& name, Shader *shader);
	bool addGeometry(const std::string& name, Geometry *geometry);
    bool addMaterial(const std::string& name, Material *material);
    
	const Shader* getShader(const std::string& name);

private:
    std::map<std::string, GeometryEntity*> geometryEntites;
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Geometry*> geometry;
    std::map<std::string, Material*> materials;
	std::map<std::string, Texture*> textures;

	Graphics() : CoreModule(CM_GRAPHICS){}
	Graphics(Graphics const&);              // Don't Implement
	void operator=(Graphics const&);		// Don't implement
    
    bool draw(const std::string &geometryKey, const std::string &materialKey);
};

#endif /* _GRAPHICS_H */
