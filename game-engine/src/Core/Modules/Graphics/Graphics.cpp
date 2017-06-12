#include "game-engine/Core/Modules/Graphics/Graphics.h"
#include "game-engine/Core/Modules/Graphics/Geometry.h"
#include "game-engine/Core/Modules/Graphics/GeometryEntity.h"

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
        entity.second->getGeometryKey();
        
        
        
    }
    
    return true;
}

bool Graphics::draw(const std::string &geometryKey, const std::string &materialKey)
{
	if (this->geometry.find(geometryKey) != this->geometry.end() && this->materials.find(materialKey) != this->materials.end())
	{
		Geometry *go = this->geometry[geometryKey];
        Material *m  = this->materials[materialKey];

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

const Shader* Graphics::getShader(const std::string& name)
{
	if (this->shaders.find(name) != this->shaders.end())
	{
		return this->shaders[name];
	}

	return NULL;
}
