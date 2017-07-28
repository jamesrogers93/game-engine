#include "game-engine/Modules/Graphics/Mesh.h"
#include "game-engine/Modules/Graphics/Vertex.h"
#include "game-engine/Modules/Graphics/Shader.h"

void MeshGL::draw() const
{
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

MeshGL* MeshGL::loadMeshGL(std::vector<VertexPNUJ> vertices, std::vector<unsigned int> indices)
{
    if(vertices.size() == 0 || indices.size() == 0)
    {
        return NULL;
    }
    
    GLuint VAO, VBO, EBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind VAO and VBOs
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexPNUJ), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    // Set the vertex attribute pointers
    size_t offset = 0;
    
    // Vertex Positions
    glEnableVertexAttribArray(ATTRIB_POSITION);
    glVertexAttribPointer(ATTRIB_POSITION, Vertex::POSITION_STRIDE, GL_FLOAT, GL_FALSE, sizeof(VertexPNUJ), (GLvoid*)0);
    offset += sizeof(glm::vec3);
    
    // Vertex Normals
    glEnableVertexAttribArray(ATTRIB_NORMAL);
    glVertexAttribPointer(ATTRIB_NORMAL, Vertex::NORMAL_STRIDE, GL_FLOAT, GL_FALSE, sizeof(VertexPNUJ), (GLvoid*)offset);
    offset += sizeof(glm::vec3);
    
    // Texture Coordinates
    glEnableVertexAttribArray(ATTRIB_UV0);
    glVertexAttribPointer(ATTRIB_UV0, Vertex::UV0_STRIDE, GL_FLOAT, GL_FALSE, sizeof(VertexPNUJ), (GLvoid*)offset);
    offset += sizeof(glm::vec2);
    
    // Joint ID
    glEnableVertexAttribArray(ATTRIB_JOINT_ID);
    glVertexAttribPointer(ATTRIB_JOINT_ID, Vertex::JOINT_STRIDE, GL_FLOAT, GL_FALSE, sizeof(VertexPNUJ), (GLvoid*)offset);
    offset += sizeof(glm::vec4);
    
    // Joint Weight
    glEnableVertexAttribArray(ATTRIB_JOINT_WEIGHT);
    glVertexAttribPointer(ATTRIB_JOINT_WEIGHT, Vertex::JOINT_STRIDE, GL_FLOAT, GL_FALSE, sizeof(VertexPNUJ), (GLvoid*)offset);
    offset += sizeof(glm::vec4);
    
    glBindVertexArray(0);
    
    return new MeshGL(VAO, VBO, EBO, (unsigned int)indices.size());
}

MeshGL* MeshGL::loadMeshGL(std::vector<VertexPU> vertices, std::vector<unsigned int> indices)
{
    if(vertices.size() == 0 || indices.size() == 0)
    {
        return NULL;
    }
    
    GLuint VAO, VBO, EBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind VAO and VBOs
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexPU), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    // Set the vertex attribute pointers
    size_t offset = 0;
    
    // Vertex Positions
    glEnableVertexAttribArray(ATTRIB_POSITION);
    glVertexAttribPointer(ATTRIB_POSITION, Vertex::POSITION_STRIDE, GL_FLOAT, GL_FALSE, sizeof(VertexPU), (GLvoid*)0);
    offset += sizeof(glm::vec3);
    
    // Texture Coordinates
    glEnableVertexAttribArray(ATTRIB_UV0);
    glVertexAttribPointer(ATTRIB_UV0, Vertex::UV0_STRIDE, GL_FLOAT, GL_FALSE, sizeof(VertexPU), (GLvoid*)offset);
    offset += sizeof(glm::vec2);
    
    glBindVertexArray(0);
    
    return new MeshGL(VAO, VBO, EBO, (unsigned int)indices.size());
}

/*MeshGL* MeshGL::loadMeshGL(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    if(vertices.size() == 0 || indices.size() == 0)
    {
        return NULL;
    }
    
    // Get size of Vertex
    unsigned int sizeOfVertex = vertices[0].sizeInBytes();
    
    // Get array of vertices
    std::vector<float> data;
    data.reserve(vertices.size() * vertices[0].getNumElements());
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        std::vector<float> vertData = vertices[i].getData();
        data.insert(std::end(data), std::begin(vertData), std::end(vertData));
    }
    
    GLuint VAO, VBO, EBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind VAO and VBOs
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeOfVertex, &data[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    // Set the vertex attribute pointers
    size_t offset = 0;
    
    // Vertex Positions
    if(vertices[0].hasPosition())
    {
        glEnableVertexAttribArray(ATTRIB_POSITION);
        glVertexAttribPointer(ATTRIB_POSITION, Vertex::POSITION_STRIDE, GL_FLOAT, GL_FALSE, sizeOfVertex, (GLvoid*)0);
        offset += vertices[0].sizeOfPosition();
    }
    
    // Vertex Normals
    if(vertices[0].hasNormal())
    {
        glEnableVertexAttribArray(ATTRIB_NORMAL);
        glVertexAttribPointer(ATTRIB_NORMAL, Vertex::NORMAL_STRIDE, GL_FLOAT, GL_FALSE, sizeOfVertex, (GLvoid*)offset);
        offset += vertices[0].sizeOfNormal();
    }
    
    // Vertex UV0s
    if(vertices[0].hasUV0())
    {
        glEnableVertexAttribArray(ATTRIB_UV0);
        glVertexAttribPointer(ATTRIB_UV0, Vertex::UV0_STRIDE, GL_FLOAT, GL_FALSE, sizeOfVertex, (GLvoid*)offset);
        offset += vertices[0].sizeOfUV0();
    }
    
    // Vertex Colours
    if(vertices[0].hasColour())
    {
        glEnableVertexAttribArray(ATTRIB_COLOUR);
        glVertexAttribPointer(ATTRIB_COLOUR, Vertex::COLOUR_STRIDE, GL_FLOAT, GL_FALSE, sizeOfVertex, (GLvoid*)offset);
        offset += vertices[0].sizeOfColour();
    }
    
    // Vertex Joint ids
    if(vertices[0].hasJointId())
    {
        glEnableVertexAttribArray(ATTRIB_JOINT_ID);
        glVertexAttribPointer(ATTRIB_JOINT_ID, Vertex::JOINT_STRIDE, GL_FLOAT, GL_FALSE, sizeOfVertex, (GLvoid*)offset);
        offset += vertices[0].sizeOfJointId();
    }
    
    // Vertex Joint weights
    if(vertices[0].hasJointWeight())
    {
        glEnableVertexAttribArray(ATTRIB_JOINT_WEIGHT);
        glVertexAttribPointer(ATTRIB_JOINT_WEIGHT, Vertex::JOINT_STRIDE, GL_FLOAT, GL_FALSE, sizeOfVertex, (GLvoid*)offset);
        //offset += vertices[0].sizeOfJointWeight());
    }
    
    glBindVertexArray(0);
    
    return new MeshGL(VAO, VBO, EBO, (unsigned int)indices.size());
}*/

/*Geometry* Geometry::loadGeometry(std::vector<Vertex3DPN> vertices, std::vector<unsigned int> indices)
{
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO and VBOs
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3DPN), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers

	// Vertex Positions
	glEnableVertexAttribArray(ATTRIB_POSITION);
	glVertexAttribPointer(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DPN), (GLvoid*)0);

	// Vertex Normals
	glEnableVertexAttribArray(ATTRIB_NORMAL);
	glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DPN), (GLvoid*)sizeof(glm::vec3));

	glBindVertexArray(0);

	return new Geometry(VAO, VBO, EBO, (unsigned int)indices.size());
}

Geometry* Geometry::loadGeometry(std::vector<Vertex3DPT> vertices, std::vector<unsigned int> indices)
{
    GLuint VAO, VBO, EBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Bind VAO and VBOs
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3DPT), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    // Set the vertex attribute pointers
    
    // Vertex Positions
    glEnableVertexAttribArray(ATTRIB_POSITION);
    glVertexAttribPointer(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DPT), (GLvoid*)0);
    
    // Vertex Normals
    glEnableVertexAttribArray(ATTRIB_TEXCOORD);
    glVertexAttribPointer(ATTRIB_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DPT), (GLvoid*)sizeof(glm::vec3));
    
    glBindVertexArray(0);
    
    return new Geometry(VAO, VBO, EBO, (unsigned int)indices.size());
}

Geometry* Geometry::loadGeometry(std::vector<Vertex3DPNT> vertices, std::vector<unsigned int> indices)
{
	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO and VBOs
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3DPNT), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers

	// Vertex Positions
	glEnableVertexAttribArray(ATTRIB_POSITION);
	glVertexAttribPointer(ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DPNT), (GLvoid*)0);

	// Vertex Normals
	glEnableVertexAttribArray(ATTRIB_NORMAL);
	glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DPNT), (GLvoid*)sizeof(glm::vec3));

	// Texture Coordinates
	glEnableVertexAttribArray(ATTRIB_UV0);
	glVertexAttribPointer(ATTRIB_UV0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DPNT), (GLvoid*)(sizeof(glm::vec3)*2));

	glBindVertexArray(0);

	return new Geometry(VAO, VBO, EBO, (unsigned int)indices.size());
}

Geometry* Geometry::loadGeometry(const std::string &file)
{
    
    
    
    return new Geometry();
}*/


