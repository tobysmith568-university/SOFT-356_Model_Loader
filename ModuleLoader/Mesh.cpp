#include "Mesh.h"


#define BUFFER_OFFSET(a) ((void*)(a))

using namespace std;

Mesh::Mesh(GLuint& _program)
	: program(_program)
{
}

void Mesh::Init()
{
	CreateAndUseVAO();
	BindVertices();
	BindIndices();
	BindTexture();
}

void Mesh::Update()
{
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, textureBuffer);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

std::vector<Vertex> Mesh::GetVertices()
{
	return vertices;
}

void Mesh::SetVertices(std::vector<Vertex> _vertices)
{
	vertices = _vertices;
}

std::vector<GLuint> Mesh::GetIndicies()
{
	return indices;
}

void Mesh::SetIndicies(std::vector<GLuint> _indicies)
{
	indices = _indicies;
}

void Mesh::SetMaterial(Material& _material)
{
	material = _material;
}

void Mesh::CreateAndUseVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void Mesh::BindVertices()
{
	glGenBuffers(1, &vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
}

void Mesh::BindIndices()
{
	glGenBuffers(1, &indicesBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(offsetof(Vertex, position)));
	glEnableVertexAttribArray(vPosition);

	glVertexAttribPointer(tPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(offsetof(Vertex, texture)));
	glEnableVertexAttribArray(tPosition);
}

void Mesh::BindTexture()
{
	glGenTextures(1, &textureBuffer);
	glBindTexture(GL_TEXTURE_2D, textureBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, material.diffuseTextureMap.GetWidth(), material.diffuseTextureMap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, material.diffuseTextureMap.GetData());
	glGenerateMipmap(GL_TEXTURE_2D);

	glUniform1i(glGetUniformLocation(program, "texture1"), 0);
}
