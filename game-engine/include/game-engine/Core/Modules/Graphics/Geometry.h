#ifndef _GEOMETRY_H
#define _GEOMETRY_H

// STL
#include <vector>
#include <string>

// Engine defines
#include "game-engine/Defines/OpenGL.h"

#include "game-engine/Core/Modules/Graphics/Vertex.h"

//struct Vertex3DPN;
//struct Vertex3DPT;
//struct Vertex3DPNT;

//class Vertex;

class GeometryGL
{
public:
	GLuint VAO, VBO, EBO;
    unsigned int indexCount;

    GeometryGL() : VAO(0), VBO(0), EBO(0) {}
	GeometryGL(const GLuint VAO, const GLuint VBO, const GLuint EBO, const unsigned int &indexCount) : VAO(VAO), VBO(VBO), EBO(EBO), indexCount(indexCount) {}
    
    void draw();
    
    static GeometryGL* loadGeometryGL(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    //static Geometry* loadGeometry(std::vector<Vertex3DPN> vertices, std::vector<unsigned int> indices);
    //static Geometry* loadGeometry(std::vector<Vertex3DPT> vertices, std::vector<unsigned int> indices);
    //static Geometry* loadGeometry(std::vector<Vertex3DPNT> vertices, std::vector<unsigned int> indices);
    static GeometryGL* loadGeometryGL(const std::string &file);
};

class Geometry
{
public:
    Geometry(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) : mVertices(vertices), mIndices(indices)
    {}
    
    const std::vector<Vertex>& getVertices() { return this->mVertices; }
    const std::vector<unsigned int> getIndices() { return this->mIndices; }
    
private:
    
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
};

#endif /* _GEOMETRY_H */
