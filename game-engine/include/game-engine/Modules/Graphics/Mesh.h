#ifndef _MESH_H
#define _MESH_H

// STL
#include <vector>
#include <string>

// Engine defines
#include "game-engine/Defines/OpenGL.h"

#include "game-engine/Modules/Graphics/Vertex.h"

//struct Vertex3DPN;
//struct Vertex3DPT;
//struct Vertex3DPNT;

//class Vertex;

class MeshGL
{
public:
	GLuint VAO, VBO, EBO;
    unsigned int indexCount;

    MeshGL() : VAO(0), VBO(0), EBO(0) {}
	MeshGL(const GLuint VAO, const GLuint VBO, const GLuint EBO, const unsigned int &indexCount) : VAO(VAO), VBO(VBO), EBO(EBO), indexCount(indexCount) {}
    
    void draw() const;
    
    static MeshGL* loadMeshGL(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    //static Geometry* loadGeometry(std::vector<Vertex3DPN> vertices, std::vector<unsigned int> indices);
    //static Geometry* loadGeometry(std::vector<Vertex3DPT> vertices, std::vector<unsigned int> indices);
    //static Geometry* loadGeometry(std::vector<Vertex3DPNT> vertices, std::vector<unsigned int> indices);
    static MeshGL* loadMeshGL(const std::string &file);
};

class Mesh
{
public:
    Mesh(const std::string &name, const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices) : mName(name), mVertices(vertices), mIndices(indices)
    {}
    
    const std::string& getName() const { return mName; }
    const std::vector<Vertex> getVertices() const { return this->mVertices; }
    const std::vector<unsigned int> getIndices() const { return this->mIndices; }
    
private:
    std::string mName;
    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;
};

#endif /* _MESH_H */
