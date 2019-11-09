#include "Model.h"

Model::Model()
{
}

std::vector<Vertex> Model::GetVertices()
{
	return vertices;
}

void Model::SetVertices(std::vector<Vertex> _vertices)
{
	vertices = _vertices;
}

std::vector<GLuint> Model::GetIndicies()
{
	return indicies;
}

void Model::SetIndicies(std::vector<GLuint> _indicies)
{
	indicies = _indicies;
}

std::vector<Texture> Model::GetTextures()
{
	return textures;
}

void Model::SetTextures(std::vector<Texture> _textures)
{
	textures = _textures;
}