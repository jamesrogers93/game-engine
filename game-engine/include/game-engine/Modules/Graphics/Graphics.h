#ifndef _GRAPHICS_H
#define _GRAPHICS_H

// STD
#include <string>
#include <unordered_map>
#include <algorithm>

// Game Engine
#include "game-engine/Modules/CoreModule.h"

class MeshProperty;
class CameraEntity;
class LightProperty;
class Shader;
class MeshGL;
class Material;
class GLTexture;

class Graphics : public CoreModule
{
public:
    
	static Graphics& getInstance()
	{
		static Graphics    instance;
		return instance;
	}

	bool initialise();
	bool deinitialise();
    bool update();

    bool addMeshProperty(const std::string&, MeshProperty*);
    bool addLightProperty(const std::string&, LightProperty*);
    bool addCameraEntity(const std::string&, CameraEntity*);
    bool addShader(const std::string&, Shader*);
	bool addMesh(const std::string&, MeshGL*);
    bool addMaterial(const std::string&, Material*);
    bool addTexture(const std::string&, GLTexture*);
    
    bool removeMeshProperty(const std::string&);
    bool removeLightProperty(const std::string&);
    bool removeCameraEntity(const std::string&);
    bool removeShader(const std::string&);
    bool removeMesh(const std::string&);
    bool removeMaterial(const std::string&);
    bool removeTexture(const std::string&);
    
    const MeshProperty* getMeshProperty(const std::string& name) const;
    const LightProperty* getLightProperty(const std::string& name) const;
    const CameraEntity* getCameraEntity(const std::string& name) const;
    const MeshGL* getMesh(const std::string& name) const;
    const Material* getMaterial(const std::string& name) const;
	const Shader* getShader(const std::string& name) const;
    const GLTexture* getTexture(const std::string &name) const;
    
    bool setActiveCameraEntity(const std::string &name);
    
    void enableBackfaceCulling();

private:
    std::unordered_map<std::string, MeshProperty*> meshProperties;
    std::unordered_map<std::string, CameraEntity*> cameraEntites;
    std::unordered_map<std::string, LightProperty*> lightProperties;
	std::unordered_map<std::string, Shader*> shaders;
	std::unordered_map<std::string, MeshGL*> meshes;
    std::unordered_map<std::string, Material*> materials;
	std::unordered_map<std::string, GLTexture*> textures;
    
    CameraEntity* activeCameraEntity;

    Graphics() : CoreModule(CoreModuleType::CM_GRAPHICS){}
	Graphics(Graphics const&);              // Don't Implement
	void operator=(Graphics const&);		// Don't implement
    
    void render();
    bool draw(MeshProperty*);
};

#endif /* _GRAPHICS_H */
