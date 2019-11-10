#include "Object.h"

Object::Object(GLuint& _program)
	: program(_program)
{
}

void Object::Init()
{
	for (size_t i = 0; i < meshes.size(); i++)
	{
		meshes[i].Init();
	}
}

void Object::Update()
{
	for (size_t i = 0; i < meshes.size(); i++)
	{
		meshes[i].Update();
	}
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