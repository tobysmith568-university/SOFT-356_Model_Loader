#include "Model.h"

using namespace std;

Model::Model(GLuint& _program)
	: program(_program)
{
	mvpBuilder = MVPBuilder()
		.AddScale(1.0f, 1.0f, 1.0f)
		.AddTranslation(0.0f, 0.0f, 0.0f);

	mvp = mvpBuilder.Build();
	UseMVP(mvp);
}

void Model::Init()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i].Init();
	}
}

void Model::Update()
{
	mvp = mvpBuilder.Build();
	UseMVP(mvp);

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i].Update();
	}
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

std::vector<Material> Model::GetMaterials()
{
	vector<Material> results = vector<Material>();

	for (auto& pair : materials)
	{
		results.push_back(pair.second);
	}

	return results;
}

MVPBuilder& Model::GetMVPBuilder()
{
	return mvpBuilder;
}

void Model::UseMVP(mat4 mvp)
{
	int mvpLoc = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
}
