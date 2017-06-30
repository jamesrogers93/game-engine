#ifndef _VERTEX_H
#define _VERTEX_H

// GLM
#include <glm/glm.hpp>

struct Vertex3DPN
{
    Vertex3DPN(const glm::vec3 &position, const glm::vec3 &normal)
    : position(position), normal(normal)
    {}
    
    Vertex3DPN(const float &px, const float &py, const float &pz, const float &nx, const float &ny, const float &nz)
    : position(glm::vec3(px, py, pz)), normal(glm::vec3(nx, ny, nz))
    {}
    
	glm::vec3 position;
	glm::vec3 normal;
};

struct Vertex3DPNT : Vertex3DPN
{
    Vertex3DPNT(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &texCoord)
    : Vertex3DPN(position, normal), texCoord(texCoord)
    {}
    
    Vertex3DPNT(const float &px, const float &py, const float &pz, const float &nx, const float &ny, const float &nz, const float &tn, const float &tv)
    : Vertex3DPN(px, py, pz, nx, ny, nz), texCoord(glm::vec2(tn, tv))
    {}
    
	glm::vec2 texCoord;
};

struct Vertex3DPT
{
    Vertex3DPT(const glm::vec3 &position, const glm::vec2 &uv)
    : position(position), uv(uv)
    {}
    
    Vertex3DPT(const float &px, const float &py, const float &pz, const float &u, const float &v)
    : position(glm::vec3(px, py, pz)), uv(glm::vec2(u, v))
    {}
    
    glm::vec3 position;
    glm::vec2 uv;
};

#endif /* _VERTEX_H */
