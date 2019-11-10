#pragma once

#include <string>
#include <vector>

#include "Vertex.h"
#include "Material.h"

class Mesh
{
public:

	std::vector<Vertex> GetVertices();
	void SetVertices(std::vector<Vertex> _vertices);

	std::vector<GLuint> GetIndicies();
	void SetIndicies(std::vector<GLuint> _indicies);

	void SetMaterial(Material& _material);

private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indicies;
	Material material;
};