#ifndef _GRAPHICS_H
#define _GRAPHICS_H

// STD
#include <string>
#include <map>
#include <algorithm>

// Game Engine
#include "game-engine/Modules/CoreModule.h"

class MeshProperty;
class CameraEntity;
class LightProperty;
class Shader;
class MeshGL;
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

    bool addMeshProperty(const std::string&, MeshProperty*);
    bool addCameraEntity(const std::string&, CameraEntity*);
    bool addLightProperty(const std::string&, LightProperty*);
    bool addShader(const std::string&, Shader*);
	bool addMesh(const std::string&, MeshGL*);
    bool addMaterial(const std::string&, Material*);
    
	Shader* getShader(const std::string& name);
    Texture* getTexture(const std::string &name);
    
    bool setActiveCameraEntity(const std::string &name);
    
    void enableBackfaceCulling();

private:
    std::map<std::string, MeshProperty*> meshProperties;
    std::map<std::string, CameraEntity*> cameraEntites;
    std::map<std::string, LightProperty*> lightProperties;
	std::map<std::string, Shader*> shaders;
	std::map<std::string, MeshGL*> meshes;
    std::map<std::string, Material*> materials;
	std::map<std::string, Texture*> textures;
    
    std::string activeCameraEntity;

	Graphics() : CoreModule(CM_GRAPHICS){}
	Graphics(Graphics const&);              // Don't Implement
	void operator=(Graphics const&);		// Don't implement
    
    bool draw(MeshProperty*);
};

#endif /* _GRAPHICS_H */
