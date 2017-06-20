#ifndef _GEOMETRY_H
#define _GEOMETRY_H

// STL
#include <vector>

// Engine defines
#include "game-engine/Defines/OpenGL.h"

struct Vertex3DPN;
struct Vertex3DPNT;

class Geometry
{
public:
	GLuint VAO, VBO, EBO;
    unsigned int indexCount;

    Geometry() : VAO(0), VBO(0), EBO(0) {}
	Geometry(const GLuint VAO, const GLuint VBO, const GLuint EBO, const unsigned int &indexCount) : VAO(VAO), VBO(VBO), EBO(EBO), indexCount(indexCount) {}
    
    static Geometry* loadGeometry(std::vector<Vertex3DPN> vertices, std::vector<unsigned int> indices);
    static Geometry* loadGeometry(std::vector<Vertex3DPNT> vertices, std::vector<unsigned int> indices);
    static Geometry* loadGeometry(const std::string &file);
};

#endif /* _GEOMETRY_H */
