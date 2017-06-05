#include "Core/Modules/Graphics/Graphics.h"
#include "Core/Modules/Graphics/Geometry.h"

bool Graphics::initalise()
{
	return true;
}

bool Graphics::deinitalise()
{

	// Delete shaders and geometry

	return true;
}

bool Graphics::draw(const std::string &name)
{
	if (this->geometry.find(name) != this->geometry.end())
	{
		Geometry *go = &this->geometry[name];

		glBindVertexArray(go->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		return true;
	}

	return false;
}

bool Graphics::addGeometry(std::string name, Geometry geometry)
{
	if (this->geometry.find(name) == this->geometry.end())
	{
		this->geometry[name] = geometry;
		return true;
	}

	return false;
}

bool Graphics::addShader(std::string name, Shader *shader)
{
	if (this->shaders.find(name) == this->shaders.end())
	{
		this->shaders[name] = shader;
		return true;
	}

	return false;
}

const Shader* Graphics::getShader(std::string name)
{
	if (this->shaders.find(name) != this->shaders.end())
	{
		return this->shaders[name];
	}

	return NULL;
}
