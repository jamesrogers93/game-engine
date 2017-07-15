#include "game-engine/Modules/Graphics/Graphics.h"
#include "game-engine/Modules/Graphics/Mesh.h"
#include "game-engine/Modules/Graphics/MeshProperty.h"
#include "game-engine/Modules/Graphics/CameraEntity.h"
#include "game-engine/Modules/Graphics/LightProperty.h"
#include "game-engine/Modules/Graphics/PointLightProperty.h"
#include "game-engine/Modules/Graphics/DirectionalLightProperty.h"
#include "game-engine/Modules/Graphics/Material.h"
#include "game-engine/Modules/Graphics/Shader.h"

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
    for(auto const &mesh : this->meshProperties)
    {
        if(!this->draw(mesh.second))
        {
            return false;
        }
    }
    
    return true;
}

bool Graphics::draw(MeshProperty* mesh)
{
    
	if (this->meshes.find(mesh->getGeometryKey()) != this->meshes.end() &&
        this->materials.find(mesh->getMaterialKey()) != this->materials.end() &&
        this->shaders.find(mesh->getShaderKey()) != this->shaders.end() &&
        this->cameraEntites.find(this->activeCameraEntity) != this->cameraEntites.end())
	{
		MeshGL *go = this->meshes[mesh->getGeometryKey()];
        Material *m  = this->materials[mesh->getMaterialKey()];
        Shader   *s  = this->shaders[mesh->getShaderKey()];
        CameraEntity *c = this->cameraEntites[this->activeCameraEntity];

        s->use();
        
        // Add lights to the shader
        unsigned int pointLightCount = 0;
        unsigned int dirLightCount = 0;
        for(auto light : this->lightProperties)
        {
            switch(light.second->getType())
            {
                case LightProperty::POINT:
                {
                    if(pointLightCount > PointLightProperty::MAX_LIGHTS)
                    {
                        continue;
                    }
                    else if(light.second->isOn())
                    {
                        light.second->loadToShader(s, pointLightCount++);
                    }
                    break;
                }
                case LightProperty::DIRECTIONAL:
                {
                    if(dirLightCount > DirectionalLightProperty::MAX_LIGHTS)
                    {
                        continue;
                    }
                    else if(light.second->isOn())
                    {
                        light.second->loadToShader(s, dirLightCount++);
                    }
                    break;
                }
                case LightProperty::UNDEFINED:
                default:
                {
                    break;
                }
            }
        }
        
        PointLightProperty::loadNumLightsToShader(s, pointLightCount);
        DirectionalLightProperty::loadNumLightsToShader(s, dirLightCount);
        
        // Load the camera data to the shader
        c->loadToShader(s);
        
        // Load the model to the shader
        mesh->loadToShader(s);
        
        // Load the material data into shader
        m->loadToShader(s);
        
        // Draw the geometry
        go->draw();

		return true;
	}

	return false;
}

bool Graphics::addMeshProperty(const std::string& name, MeshProperty* property)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
    if (this->meshProperties.find(nameLow) == this->meshProperties.end())
    {
        this->meshProperties[nameLow] = property;
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

bool Graphics::addLightProperty(const std::string& name, LightProperty* lightProperty)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
    if (this->lightProperties.find(nameLow) == this->lightProperties.end())
    {
        this->lightProperties[nameLow] = lightProperty;
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

bool Graphics::addMesh(const std::string& name, MeshGL *mesh)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
	if (this->meshes.find(nameLow) == this->meshes.end())
	{
		this->meshes[nameLow] = mesh;
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

void Graphics::enableBackfaceCulling()
{
    //glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
}


