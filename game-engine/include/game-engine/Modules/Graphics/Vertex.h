#ifndef _VERTEX_H
#define _VERTEX_H

// STD
#include <vector>

// GLM
#include <glm/glm.hpp>

struct VertexElement
{
    union element
    {
        int i;
        float f;
    };
};

class VertexBase
{
protected:
    bool mHasPosition = false;
    bool mHasNormal = false;
    bool mHasUV0 = false;
    bool mHasColour = false;
    bool mHasJointId = false;
    bool mHasJointWeight = false;
    
    VertexBase(){}
    
public:
    const bool& hasPosition() { return this->mHasPosition; }
    const bool& hasNormal() { return this->mHasNormal; }
    const bool& hasUV0() { return this->mHasUV0; }
    const bool& hasColour() { return this->mHasColour; }
    const bool& hasJointId() { return this->mHasJointId; }
    const bool& hasJointWeight() { return this->mHasJointWeight; }
};

class Vertex : public VertexBase
{
public:
    static const unsigned int POSITION_STRIDE = 3;
    static const unsigned int NORMAL_STRIDE = 3;
    static const unsigned int UV0_STRIDE = 2;
    static const unsigned int COLOUR_STRIDE = 4;
    static const unsigned int JOINT_STRIDE = 4;
    
    Vertex() : VertexBase() {}
    
    const glm::vec3& getPosition() const { return this->mPosition; }
    const glm::vec3& getNormal() const { return this->mNormal; }
    const glm::vec2& getUV0() const { return this->mUv0; }
    const glm::vec4& getColour() const { return this->mColour; }
    const glm::vec4& getJointId() const { return this->mJointId; }
    const glm::vec4& getJointWeight() const { return this->mJointWeight; }
    
    void setPosition(const glm::vec3 &position) { this->mPosition = position; this->mHasPosition = true; }
    void setNormal(const glm::vec3 &normal) { this->mNormal = normal; this->mHasNormal = true; }
    void setUV0(const glm::vec2 &uv0) { this->mUv0 = uv0; this->mHasUV0 = true; }
    void setColour(const glm::vec4 &colour) { this->mColour = colour; this->mHasColour = true; }
    void setJointId(const glm::vec4 &jointId) { this-> mJointId = jointId; this->mHasJointId = true; }
    void setJointWeight(const glm::vec4 &jointWeight) { this-> mJointWeight = jointWeight; this->mHasJointWeight = true; }
    
    unsigned int getNumElements()
    {
        unsigned int num = 0;
        if(mHasPosition)
        {
            num += POSITION_STRIDE;
        }
        if(mHasNormal)
        {
            num += NORMAL_STRIDE;
        }
        if(mHasUV0)
        {
            num += UV0_STRIDE;
        }
        if(mHasColour)
        {
            num += COLOUR_STRIDE;
        }
        if(mHasJointId)
        {
            num += JOINT_STRIDE;
        }
        if(mHasJointWeight)
        {
            num += JOINT_STRIDE;
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
        if(mHasJointId)
        {
            size += sizeof(glm::vec4);
        }
        if(mHasJointWeight)
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
    
    unsigned int sizeOfJointId()
    {
        return sizeof(glm::vec4);
    }
    
    unsigned int sizeOfJointWeight()
    {
        return sizeof(glm::vec4);
    }
    
    std::vector<float> getData()
    {
        std::vector<float> data;
        
        if(mHasPosition)
        {
            data.push_back(mPosition.x);
            data.push_back(mPosition.y);
            data.push_back(mPosition.z);
        }
        if(mHasNormal)
        {
            data.push_back(mNormal.x);
            data.push_back(mNormal.y);
            data.push_back(mNormal.z);
        }
        if(mHasUV0)
        {
            data.push_back(mUv0.x);
            data.push_back(mUv0.y);
        }
        if(mHasColour)
        {
            data.push_back(mColour.r);
            data.push_back(mColour.g);
            data.push_back(mColour.b);
            data.push_back(mColour.a);
        }
        if(mHasJointId)
        {
            data.push_back(mJointId.x);
            data.push_back(mJointId.y);
            data.push_back(mJointId.z);
            data.push_back(mJointId.w);
        }
        if(mHasJointWeight)
        {
            data.push_back(mJointWeight.x);
            data.push_back(mJointWeight.y);
            data.push_back(mJointWeight.z);
            data.push_back(mJointWeight.w);
        }
        
        return data;
    }
    
private:
    glm::vec3 mPosition;
    glm::vec3 mNormal;
    glm::vec2 mUv0;
    glm::vec4 mColour;
    glm::vec4 mJointId;
    glm::vec4 mJointWeight;
    
};

class VertexIndex : public VertexBase
{
public:
    unsigned int getPosition(){ return this->mPosition; }
    unsigned int getNormal(){ return this->mNormal; }
    unsigned int getUV0(){ return this->mUv0; }
    unsigned int getColour(){ return this->mColour; }
    unsigned int getJointId(){ return this->mJointId; }
    unsigned int getJointWeight(){ return this->mJointWeight; }
    
    void setPosition(const unsigned int &position) { this->mPosition = position; this->mHasPosition = true; }
    void setNormal(const unsigned int &normal) { this->mNormal = normal; this->mHasNormal = true; }
    void setUV0(const unsigned int &uv0) { this->mUv0 = uv0; this->mHasUV0 = true; }
    void setColour(const unsigned int &colour) { this->mColour = colour; this->mHasColour = true; }
    void setJointId(const unsigned int &jointId) { this-> mJointId = jointId; this->mHasJointId = true; }
    void setJointWeight(const unsigned int &jointWeight) { this-> mJointWeight = jointWeight; this->mHasJointWeight = true; }
    
    VertexIndex() : VertexBase() {}
    
    bool operator<( const VertexIndex& rhs ) const
    {
        if ( mPosition < rhs.mPosition )
                return true;
     
        if ( mPosition > rhs.mPosition )
                return false;
     
        if ( mNormal < rhs.mNormal )
                return true;
     
        if ( mNormal > rhs.mNormal )
                return false;
     
        if ( mUv0 < rhs.mUv0 )
                return true;
     
        if ( mUv0 > rhs.mUv0 )
                return false;
     
        if ( mColour < rhs.mColour )
                return true;
     
        if ( mColour > rhs.mColour )
            return false;
        
        if ( mJointId < rhs.mJointId )
            return true;
        
        if ( mJointId > rhs.mJointId )
            return false;
        
        if ( mJointWeight < rhs.mJointWeight )
            return true;
        
        if ( mJointWeight > rhs.mJointWeight )
            return false;
     
        return false;
    }

private:
    unsigned int mPosition;
    unsigned int mNormal;
    unsigned int mUv0;
    unsigned int mColour;
    unsigned int mJointId;
    unsigned int mJointWeight;

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
