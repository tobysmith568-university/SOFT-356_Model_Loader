#include "Model.h"

Model::Model()
{
}

std::vector<GLfloat> Model::GetVertices()
{
	return vertices;
}

void Model::SetVertices(std::vector<GLfloat> _vertices)
{
	vertices = _vertices;
}

std::vector<GLuint> Model::GetTriangles()
{
	return triangles;
}

void Model::SetTriangles(std::vector<GLuint> _triangles)
{
	triangles = _triangles;
}

std::vector<GLfloat> Model::GetColours()
{
	return colours;
}

void Model::SetColours(std::vector<GLfloat> _colours)
{
	colours = _colours;
}

std::vector<GLfloat> Model::GetTextureCoords()
{
	return textureCoords;
}

void Model::SetTextureCoords(std::vector<GLfloat> _textureCoords)
{
	textureCoords = _textureCoords;
}

std::vector<Texture> Model::GetTextures()
{
	return textures;
}

void Model::SetTextures(std::vector<Texture> _textures)
{
	textures = _textures;
}