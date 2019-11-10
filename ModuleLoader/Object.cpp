#include "Object.h"

Object::Object()
{
}

void Object::SetName(std::string& _name)
{
	name = _name;
}

std::string& Object::GetName()
{
	return name;
}

void Object::AddMesh(Mesh& mesh)
{
	meshes.push_back(mesh);
}

std::vector<Mesh>& Object::GetMeshes()
{
	return meshes;
}