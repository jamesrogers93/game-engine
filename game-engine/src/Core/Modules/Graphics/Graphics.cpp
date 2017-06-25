#include "game-engine/Core/Modules/Graphics/Graphics.h"
#include "game-engine/Core/Modules/Graphics/Geometry.h"
#include "game-engine/Core/Modules/Graphics/GeometryEntity.h"
#include "game-engine/Core/Modules/Graphics/CameraEntity.h"
#include "game-engine/Core/Modules/Graphics/LightEntity.h"
#include "game-engine/Core/Modules/Graphics/Material.h"
#include "game-engine/Core/Modules/Graphics/Shader.h"

const unsigned int Graphics::MAX_LIGHTS = 4;

bool Graphics::initalise()
{
	return true;
}

bool Graphics::deinitalise()
{

	// Delete shaders and geometry

	return true;
}

bool Graphics::update()
{
    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for(auto const &entity : this->geometryEntites)
    {
        if(!this->draw(entity.second))
        {
            return false;
        }
    }
    
    return true;
}

bool Graphics::draw(GeometryEntity* entity)
{
    
	if (this->geometry.find(entity->getGeometryKey()) != this->geometry.end() &&
        this->materials.find(entity->getMaterialKey()) != this->materials.end() &&
        this->shaders.find(entity->getShaderKey()) != this->shaders.end() &&
        this->cameraEntites.find(this->activeCameraEntity) != this->cameraEntites.end())
	{
		Geometry *go = this->geometry[entity->getGeometryKey()];
        Material *m  = this->materials[entity->getMaterialKey()];
        Shader   *s  = this->shaders[entity->getShaderKey()];
        CameraEntity *c = this->cameraEntites[this->activeCameraEntity];

        s->use();
        
        // Add lights to the shader
        unsigned int lightCount = 0;
        for(auto light : this->lightEntites)
        {
            if(lightCount > MAX_LIGHTS)
            {
                break;
            }
            
            if(light.second->isOn())
            {
                light.second->loadToShader(s, lightCount++);
            }
        }
        LightEntity::loadNumLightsToShader(s, lightCount);
        
        // Load the camera data to the shader
        c->loadToShader(s);
        
        // Load the model to the shader
        entity->loadToShader(s);
        
        // Load the material data into shader
        m->loadToShader(s);
        
        // Draw the geometry
        go->draw();

		return true;
	}

	return false;
}

bool Graphics::addGeometryEntity(const std::string& name, GeometryEntity* geometryEntity)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
    if (this->geometryEntites.find(nameLow) == this->geometryEntites.end())
    {
        this->geometryEntites[nameLow] = geometryEntity;
        return true;
    }
    
    return false;
}

bool Graphics::addCameraEntity(const std::string& name, CameraEntity* cameraEntity)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
    if (this->cameraEntites.find(nameLow) == this->cameraEntites.end())
    {
        this->cameraEntites[nameLow] = cameraEntity;
        return true;
    }
    
    return false;
}

bool Graphics::addLightEntity(const std::string& name, LightEntity* lightEntity)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
    if (this->lightEntites.find(nameLow) == this->lightEntites.end())
    {
        this->lightEntites[nameLow] = lightEntity;
        return true;
    }
    
    return false;
}

bool Graphics::addShader(const std::string& name, Shader *shader)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
    if (this->shaders.find(nameLow) == this->shaders.end())
    {
        this->shaders[nameLow] = shader;
        return true;
    }
    
    return false;
}

bool Graphics::addGeometry(const std::string& name, Geometry *geometry)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
	if (this->geometry.find(nameLow) == this->geometry.end())
	{
		this->geometry[nameLow] = geometry;
		return true;
	}

	return false;
}

bool Graphics::addMaterial(const std::string& name, Material *material)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
    if (this->materials.find(nameLow) == this->materials.end())
    {
        this->materials[nameLow] = material;
        return true;
    }
    
    return false;
}

Shader* Graphics::getShader(const std::string& name)
{
	if (this->shaders.find(name) != this->shaders.end())
	{
		return this->shaders[name];
	}

	return NULL;
}

Texture* Graphics::getTexture(const std::string &name)
{
    if (this->textures.find(name) != this->textures.end())
    {
        return this->textures[name];
    }
    
    return NULL;
}

bool Graphics::setActiveCameraEntity(const std::string &name)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
    if(this->cameraEntites.find(nameLow) != this->cameraEntites.end())
    {
        return false;
    }
    
    this->activeCameraEntity = nameLow;
    return true;
}


