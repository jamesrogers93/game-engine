#ifndef _GRAPHICS_H
#define _GRAPHICS_H

// STD
#include <string>
#include <map>
#include <algorithm>

// Game Engine
#include "game-engine/Modules/CoreModule.h"

class GeometryEntity;
class CameraEntity;
class LightEntity;
class Shader;
class GeometryGL;
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
    bool addCameraEntity(const std::string& name, CameraEntity* cameraEntity);
    bool addLightEntity(const std::string& name, LightEntity* lightEntity);
    bool addShader(const std::string& name, Shader *shader);
	bool addGeometry(const std::string& name, GeometryGL *geometry);
    bool addMaterial(const std::string& name, Material *material);
    
	Shader* getShader(const std::string& name);
    Texture* getTexture(const std::string &name);
    
    bool setActiveCameraEntity(const std::string &name);
    
    void enableBackfaceCulling();

private:
    std::map<std::string, GeometryEntity*> geometryEntites;
    std::map<std::string, CameraEntity*> cameraEntites;
    std::map<std::string, LightEntity*> lightEntites;
	std::map<std::string, Shader*> shaders;
	std::map<std::string, GeometryGL*> geometry;
    std::map<std::string, Material*> materials;
	std::map<std::string, Texture*> textures;
    
    std::string activeCameraEntity;

	Graphics() : CoreModule(CM_GRAPHICS){}
	Graphics(Graphics const&);              // Don't Implement
	void operator=(Graphics const&);		// Don't implement
    
    bool draw(GeometryEntity* entity);
};

#endif /* _GRAPHICS_H */
