#ifndef _VERTEX_H
#define _VERTEX_H

// STD
#include <vector>

// GLM
#include <glm/glm.hpp>

class Vertex
{
public:
    static const unsigned int POSITION_STRIDE = 3;
    static const unsigned int NORMAL_STRIDE = 3;
    static const unsigned int UV0_STRIDE = 2;
    static const unsigned int COLOUR_STRIDE = 4;
    
    void setPosition(const glm::vec3 &position) { this->position = position; this->mHasPosition = true; }
    void setNormal(const glm::vec3 &normal) { this->normal = normal; this->mHasNormal = true; }
    void setUV0(const glm::vec2 &uv0) { this->uv0 = uv0; this->mHasUV0 = true; }
    void setColour(const glm::vec4 &colour) { this->colour = colour; this->mHasColour = true; }
    
    const bool& hasPosition() { return this->mHasPosition; }
    const bool& hasNormal() { return this->mHasNormal; }
    const bool& hasUV0() { return this->mHasUV0; }
    const bool& hasColour() { return this->mHasColour; }
    
    unsigned int getNumElements()
    {
        unsigned int num = 0;
        if(mHasPosition)
        {
            num += 3;
        }
        if(mHasNormal)
        {
            num += 3;
        }
        if(mHasUV0)
        {
            num += 2;
        }
        if(mHasColour)
        {
            num += 4;
        }
        
        return num;
    }
    
    unsigned int sizeInBytes()
    {
        unsigned int size = 0;
        if(mHasPosition)
        {
            size += sizeof(glm::vec3);
        }
        if(mHasNormal)
        {
            size += sizeof(glm::vec3);
        }
        if(mHasUV0)
        {
            size += sizeof(glm::vec2);
        }
        if(mHasColour)
        {
            size += sizeof(glm::vec4);
        }
        
        return size;
    }
    
    unsigned int sizeOfPosition()
    {
        return sizeof(glm::vec3);
    }
    
    unsigned int sizeOfNormal()
    {
        return sizeof(glm::vec3);
    }
    
    unsigned int sizeOfUV0()
    {
        return sizeof(glm::vec2);
    }
    
    unsigned int sizeOfColour()
    {
        return sizeof(glm::vec4);
    }
    
    std::vector<float> getData()
    {
        std::vector<float> data;
        
        if(mHasPosition)
        {
            data.push_back(position.x);
            data.push_back(position.y);
            data.push_back(position.z);
        }
        if(mHasNormal)
        {
            data.push_back(normal.x);
            data.push_back(normal.y);
            data.push_back(normal.z);
        }
        if(mHasUV0)
        {
            data.push_back(uv0.x);
            data.push_back(uv0.y);
        }
        if(mHasColour)
        {
            data.push_back(colour.r);
            data.push_back(colour.g);
            data.push_back(colour.b);
            data.push_back(colour.a);
        }
        
        return data;
    }
    
private:
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv0;
    glm::vec4 colour;
    
    bool mHasPosition = false;
    bool mHasNormal = false;
    bool mHasUV0 = false;
    bool mHasColour = false;
    
};

/*struct Vertex3DPN
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
};*/

#endif /* _VERTEX_H */
