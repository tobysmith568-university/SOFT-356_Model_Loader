#pragma once

#include "GLFW/glfw3.h"

#include "Texture.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Object.h"
#include "Material.h"

#include <vector>
#include <map>

class Model
{
public:
	Model();

	void AddObject(Object& object);
	std::vector<Object>& GetObjects();

	void AddMaterial(Material& material);
	Material& GetMaterial(std::string& name);

private:
	std::vector<Object> objects;
	std::map<std::string, Material> materials;
};