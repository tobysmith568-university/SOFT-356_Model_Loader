#pragma once
#include <vector>
#include "GLFW/glfw3.h"

#include "Texture.h"
#include "Vertex.h"

class Model
{
public:
	Model();

	std::vector<Vertex> GetVertices();
	void SetVertices(std::vector<Vertex> _vertices);

	std::vector<GLuint> GetIndicies();
	void SetIndicies(std::vector<GLuint> _indicies);

	std::vector<Texture> GetTextures();
	void SetTextures(std::vector<Texture> _textures);

private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indicies;

	std::vector<Texture> textures;
};