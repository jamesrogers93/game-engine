#include "game-engine/Core/Modules/Graphics/Geometry.h"
#include "game-engine/Core/Modules/Graphics/Vertex.h"
#include "game-engine/Core/Modules/Graphics/Shader.h"



Geometry* loadGeometry(std::vector<Vertex3DPN> vertices, std::vector<unsigned int> indices)
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
	glEnableVertexAttribArray(POSITION_ATTRIB);
	glVertexAttribPointer(POSITION_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DPN), (GLvoid*)0);

	// Vertex Normals
	glEnableVertexAttribArray(NORMAL_ATTRIB);
	glVertexAttribPointer(NORMAL_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DPN), (GLvoid*)sizeof(glm::vec3));

	glBindVertexArray(0);

	return new Geometry(VAO, VBO, EBO);
}

Geometry* loadGeometry(std::vector<Vertex3DPNT> vertices, std::vector<unsigned int> indices)
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
	glEnableVertexAttribArray(POSITION_ATTRIB);
	glVertexAttribPointer(POSITION_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DPNT), (GLvoid*)0);

	// Vertex Normals
	glEnableVertexAttribArray(NORMAL_ATTRIB);
	glVertexAttribPointer(NORMAL_ATTRIB, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DPNT), (GLvoid*)sizeof(glm::vec3));

	// Texture Coordinates
	glEnableVertexAttribArray(TEXCOORD_ATTRIB);
	glVertexAttribPointer(TEXCOORD_ATTRIB, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DPNT), (GLvoid*)(sizeof(glm::vec3)*2));

	glBindVertexArray(0);

	return new Geometry(VAO, VBO, EBO);
}


