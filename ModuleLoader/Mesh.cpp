#include "Mesh.h"

using namespace std;

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
	return indicies;
}

void Mesh::SetIndicies(std::vector<GLuint> _indicies)
{
	indicies = _indicies;
}

void Mesh::SetMaterial(Material& _material)
{
	material = _material;
}
