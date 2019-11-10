#include "Model.h"

Model::Model()
{
}

void Model::AddObject(Object& object)
{
	objects.push_back(object);
}

std::vector<Object>& Model::GetObjects()
{
	return objects;
}

void Model::AddMaterial(Material& material)
{
	materials[material.name] = material;
}

Material& Model::GetMaterial(std::string& name)
{
	return materials[name];
}