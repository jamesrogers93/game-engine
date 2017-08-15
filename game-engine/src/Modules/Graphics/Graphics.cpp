#include "game-engine/Modules/Graphics/Graphics.h"
#include "game-engine/Modules/Graphics/Mesh.h"
#include "game-engine/Modules/Graphics/MeshProperty.h"
#include "game-engine/Modules/Graphics/AnimatableMeshProperty.h"
#include "game-engine/Modules/Graphics/CameraEntity.h"
#include "game-engine/Modules/Graphics/LightProperty.h"
#include "game-engine/Modules/Graphics/PointLightProperty.h"
#include "game-engine/Modules/Graphics/DirectionalLightProperty.h"
#include "game-engine/Modules/Graphics/Material.h"
#include "game-engine/Modules/Graphics/Shader.h"

#include "game-engine/Core/GL/GLTexture.h"

#include "game-engine/Util/StringUtil.h"

#include "game-engine/Defines/OpenGL.h"

bool Graphics::initialise()
{
	return true;
}

bool Graphics::deinitialise()
{

	// Delete shaders and geometry

	return true;
}

bool Graphics::update()
{
    //GLThread::getInstance().giveJob(std::bind(&Graphics::render, this));
    
    render();
    return true;
}

void Graphics::render()
{
    //for(auto const &mesh : this->meshProperties)
    //{
    //    this->draw(mesh.second);
        //if(!this->draw(mesh.second))
        //{
        //    return false;
        //}
    //}
    
    // TEST
    if(activeCameraEntity == NULL)
    {
        return;
    }
    
    for(auto const &shader : this->shaders)
    {
        shader.second->use();
        
        // Load the camera data to the shader
        if(shader.second->getHasCamera())
        {
            activeCameraEntity->loadToShader(shader.second);
        }
        
        if(shader.second->getHasLighting())
        {
            unsigned int pointLightCount = 0;
            unsigned int dirLightCount = 0;
            for(auto light : this->lightProperties)
            {
                switch(light.second->getType())
                {
                    case Property::POINT_LIGHT:
                    {
                        if(pointLightCount > PointLightProperty::MAX_LIGHTS)
                        {
                            continue;
                        }
                        else if(light.second->isOn())
                        {
                            light.second->loadToShader(shader.second, pointLightCount++);
                        }
                        break;
                    }
                    case Property::DIRECTIONAL_LIGHT:
                    {
                        if(dirLightCount > DirectionalLightProperty::MAX_LIGHTS)
                        {
                            continue;
                        }
                        else if(light.second->isOn())
                        {
                            light.second->loadToShader(shader.second, dirLightCount++);
                        }
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        
            PointLightProperty::loadNumLightsToShader(shader.second, pointLightCount);
            DirectionalLightProperty::loadNumLightsToShader(shader.second, dirLightCount);
        
        }
        
        for(auto const &mesh : this->meshProperties)
        {
            if(mesh.second->getShaderKey() != shader.first)
            {
                continue;
            }
            
            // Load the model to the shader
            mesh.second->loadToShader(shader.second);         // Causes a ~7% increase in cpu usage
            
            // Load the material data into shader
            //Material *m  = this->materials[mesh.second->getMaterialKey()];
            const Material *m = mesh.second->getMaterialPtr();
            m->loadToShader(shader.second);
            
            // Draw the geometry
            //MeshGL *go = this->meshes[mesh.second->getMeshKey()];
            const MeshGL *go = mesh.second->getMeshPtr();
            
            //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
            go->draw(mesh.second->getDrawMode());
        }
    }
    
}

bool Graphics::draw(MeshProperty* mesh)
{
    
	//if (this->meshes.find(mesh->getMeshKey()) != this->meshes.end() &&
    //    this->materials.find(mesh->getMaterialKey()) != this->materials.end() &&
    //    this->shaders.find(mesh->getShaderKey()) != this->shaders.end() &&
    //    this->cameraEntites.find(this->activeCameraEntity) != this->cameraEntites.end())
	//{
	/*	MeshGL *go = this->meshes[mesh->getMeshKey()];
        Material *m  = this->materials[mesh->getMaterialKey()];
        Shader   *s  = this->shaders[mesh->getShaderKey()];
        //CameraEntity *c = this->cameraEntites[this->activeCameraEntity];

        s->use();
        
        // Add lights to the shader
        unsigned int pointLightCount = 0;
        unsigned int dirLightCount = 0;
        for(auto light : this->lightProperties)
        {
            switch(light.second->getType())
            {
                case Property::POINT_LIGHT:
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
                case Property::DIRECTIONAL_LIGHT:
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
                default:
                {
                    break;
                }
            }
        }
        
        PointLightProperty::loadNumLightsToShader(s, pointLightCount);
        DirectionalLightProperty::loadNumLightsToShader(s, dirLightCount);
        
        // Load the camera data to the shader
        activeCameraEntity->loadToShader(s);
        
        // Load the model to the shader
        mesh->loadToShader(s);
        
        // Load the material data into shader
        m->loadToShader(s);
        
        // Draw the geometry
        go->draw();

		return true;
	//}
*/
	return false;
}

bool Graphics::addMeshProperty(const std::string& name, MeshProperty* property)
{
    // Make name lower case
    std::string nameLow = toLower(name);
    
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
    std::string nameLow = toLower(name);
    
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
    std::string nameLow = toLower(name);
    
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
    std::string nameLow = toLower(name);
    
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
    std::string nameLow = toLower(name);
    
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
    std::string nameLow = toLower(name);
    
    if (this->materials.find(nameLow) == this->materials.end())
    {
        this->materials[nameLow] = material;
        return true;
    }
    
    return false;
}

bool Graphics::addTexture(const std::string &name, GLTexture *texture)
{
    // Make name lower case
    std::string nameLow = toLower(name);
    
    if (this->textures.find(nameLow) == this->textures.end())
    {
        this->textures[nameLow] = texture;
        return true;
    }
    
    return false;
}

bool Graphics::removeMeshProperty(const std::string& name)
{
    std::string nameLow = toLower(name);
    
    std::unordered_map<std::string, MeshProperty*>::iterator it = this->meshProperties.find(nameLow);
    if ( it != this->meshProperties.end())
    {
        this->meshProperties.erase(it);
        return true;
    }
    
    return false;
}

bool Graphics::removeLightProperty(const std::string& name)
{
    std::string nameLow = toLower(name);
    
    std::unordered_map<std::string, LightProperty*>::iterator it = this->lightProperties.find(nameLow);
    if ( it != this->lightProperties.end())
    {
        this->lightProperties.erase(it);
        return true;
    }
    
    return false;
}

bool Graphics::removeCameraEntity(const std::string& name)
{
    std::string nameLow = toLower(name);
    
    std::unordered_map<std::string, CameraEntity*>::iterator it = this->cameraEntites.find(nameLow);
    if ( it != this->cameraEntites.end())
    {
        this->cameraEntites.erase(it);
        return true;
    }
    
    return false;
}

bool Graphics::removeShader(const std::string& name)
{
    std::string nameLow = toLower(name);
    
    std::unordered_map<std::string, Shader*>::iterator it = this->shaders.find(nameLow);
    if ( it != this->shaders.end())
    {
        this->shaders.erase(it);
        return true;
    }
    
    return false;
}

bool Graphics::removeMesh(const std::string& name)
{
    std::string nameLow = toLower(name);
    
    std::unordered_map<std::string, MeshGL*>::iterator it = this->meshes.find(nameLow);
    if ( it != this->meshes.end())
    {
        this->meshes.erase(it);
        return true;
    }
    
    return false;
}

bool Graphics::removeMaterial(const std::string& name)
{
    std::string nameLow = toLower(name);
    
    std::unordered_map<std::string, Material*>::iterator it = this->materials.find(nameLow);
    if ( it != this->materials.end())
    {
        this->materials.erase(it);
        return true;
    }
    
    return false;
}

bool Graphics::removeTexture(const std::string &name)
{
    std::string nameLow = toLower(name);
    
    std::unordered_map<std::string, GLTexture*>::iterator it = this->textures.find(nameLow);
    if ( it != this->textures.end())
    {
        this->textures.erase(it);
        return true;
    }
    
    return false;
}

const MeshProperty* Graphics::getMeshProperty(const std::string &name) const
{
    if (this->meshProperties.find(name) != this->meshProperties.end())
    {
        return this->meshProperties.at(name);
    }
    
    return NULL;
}

const LightProperty* Graphics::getLightProperty(const std::string &name) const
{
    if (this->lightProperties.find(name) != this->lightProperties.end())
    {
        return this->lightProperties.at(name);
    }
    
    return NULL;
}

const CameraEntity* Graphics::getCameraEntity(const std::string &name) const
{
    if (this->cameraEntites.find(name) != this->cameraEntites.end())
    {
        return this->cameraEntites.at(name);
    }
    
    return NULL;
}

const MeshGL* Graphics::getMesh(const std::string &name) const
{
    if (this->meshes.find(name) != this->meshes.end())
    {
        return this->meshes.at(name);
    }
    
    return NULL;
}

const Material* Graphics::getMaterial(const std::string &name) const
{
    if (this->materials.find(name) != this->materials.end())
    {
        return this->materials.at(name);
    }
    
    return NULL;
}

const Shader* Graphics::getShader(const std::string &name) const
{
	if (this->shaders.find(name) != this->shaders.end())
	{
		return this->shaders.at(name);
	}

	return NULL;
}

const GLTexture* Graphics::getTexture(const std::string &name) const
{
    if (this->textures.find(name) != this->textures.end())
    {
        return this->textures.at(name);
    }
    
    return NULL;
}

bool Graphics::setActiveCameraEntity(const std::string &name)
{
    // Make name lower case
    std::string nameLow = name;
    std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
    
    if(this->cameraEntites.find(nameLow) == this->cameraEntites.end())
    {
        return false;
    }
    
    activeCameraEntity = cameraEntites.at(nameLow);
    return true;
}

void Graphics::enableBackfaceCulling()
{
    //glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
}

void Graphics::enableBlend()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


