#pragma once

// STL
#include <vector>

#include "game-engine/Defines/OpenGL.h"

class Geometry
{
public:
	GLuint VAO, VBO, EBO;

	Geometry() {}
	Geometry(const GLuint VAO, const GLuint VBO, const GLuint EBO) : VAO(VAO), VBO(VBO), EBO(EBO) {}
};

struct Vertex3DPN;
struct Vertex3DPNT;

static Geometry loadGeometry(std::vector<Vertex3DPN> vertices, std::vector<unsigned int> indices);
static Geometry loadGeometry(std::vector<Vertex3DPNT> vertices, std::vector<unsigned int> indices);


