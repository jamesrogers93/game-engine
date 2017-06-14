#include "game-engine/Core/Modules/Graphics/Graphics.h"
#include "game-engine/Core/Modules/Graphics/Geometry.h"
#include "game-engine/Core/Modules/Graphics/GeometryEntity.h"
#include "game-engine/Core/Modules/Graphics/Material.h"
#include "game-engine/Core/Modules/Graphics/Shader.h"

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
    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	if (this->geometry.find(entity->getGeometryKey()) != this->geometry.end() &&
        this->materials.find(entity->getMaterialKey()) != this->materials.end() &&
        this->shaders.find(entity->getShaderKey()) != this->shaders.end())
	{
		Geometry *go = this->geometry[entity->getGeometryKey()];
        Material *m  = this->materials[entity->getMaterialKey()];
        Shader   *s  = this->shaders[entity->getShaderKey()];

        s->use();
        // Load the material data into shader
        m->loadToShader(s);
        
		glBindVertexArray(go->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		return true;
	}

	return false;
}

bool Graphics::addGeometryEntity(const std::string& name, GeometryEntity* geometryEntity)
{
    if (this->geometryEntites.find(name) == this->geometryEntites.end())
    {
        this->geometryEntites[name] = geometryEntity;
        return true;
    }
    
    return false;
}

bool Graphics::addShader(const std::string& name, Shader *shader)
{
    if (this->shaders.find(name) == this->shaders.end())
    {
        this->shaders[name] = shader;
        return true;
    }
    
    return false;
}

bool Graphics::addGeometry(const std::string& name, Geometry *geometry)
{
	if (this->geometry.find(name) == this->geometry.end())
	{
		this->geometry[name] = geometry;
		return true;
	}

	return false;
}

bool Graphics::addMaterial(const std::string& name, Material *material)
{
    if (this->materials.find(name) == this->materials.end())
    {
        this->materials[name] = material;
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


