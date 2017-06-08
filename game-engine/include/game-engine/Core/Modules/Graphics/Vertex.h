#pragma once

// GLM
#include <glm/glm.hpp>

struct Vertex3DPN
{
	glm::vec3 position;
	glm::vec3 normal;
};

struct Vertex3DPNT : Vertex3DPN
{
	glm::vec3 texCoord;
};
