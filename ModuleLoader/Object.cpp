#include "Object.h"

Object::Object(GLuint& _program)
	: program(_program)
{
}

// OpenGL Setup
void Object::Init()
{
	for (size_t i = 0; i < meshes.size(); i++)// For every mesh
	{
		meshes[i].Init();// Init it
	}
}

// To be run every game tick
void Object::Update()
{
	for (size_t i = 0; i < meshes.size(); i++)// For every mesh
	{
		meshes[i].Update();// Update it
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