#pragma once
#include <vector>
#include "GLFW/glfw3.h"

class Model
{
public:
	Model();

	std::vector<GLfloat> GetVertices();
	void SetVertices(std::vector<GLfloat> _vertices);

	std::vector<GLuint> GetTriangles();
	void SetTriangles(std::vector<GLuint> _triangles);

	std::vector<GLfloat> GetColours();
	void SetColours(std::vector<GLfloat> _colours);

	std::vector<GLfloat> GetTextureCoords();
	void SetTextureCoords(std::vector<GLfloat> _textureCoords);


private:
	std::vector<GLfloat> vertices;
	std::vector<GLuint> triangles;
	std::vector<GLfloat> colours;
	std::vector<GLfloat> textureCoords;
};