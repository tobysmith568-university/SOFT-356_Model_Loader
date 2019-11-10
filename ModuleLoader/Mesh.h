#pragma once

#include <GL\glew.h>
#include <string>
#include <vector>

#include "Vertex.h"
#include "Material.h"

class Mesh
{
public:
	Mesh(GLuint& _program);
	void Init();
	void Update();

	std::vector<Vertex> GetVertices();
	void SetVertices(std::vector<Vertex> _vertices);

	std::vector<GLuint> GetIndicies();
	void SetIndicies(std::vector<GLuint> _indicies);

	void SetMaterial(Material& _material);

	void CreateAndUseVAO();
	void BindVertices();
	void BindIndices();
	void BindTexture();

private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	Material material;

	enum Attrib_IDs { vPosition = 0, cPosition = 1, tPosition = 2 };

	GLuint& program;

	GLuint VAO;

	GLuint vertexBuffer;
	GLuint indicesBuffer;
	GLuint textureBuffer;
};