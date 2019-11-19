#include "Model.h"

using namespace std;

Model::Model(GLuint& _program)
	: program(_program)
{
	// Create an MVP builder with some default values
	mvpBuilder = MVPBuilder()
		.AddScale(1.0f, 1.0f, 1.0f)
		.AddTranslation(0.0f, 0.0f, 0.0f);

	mvp = mvpBuilder.Build();// Create and use an MVP
	UseMVP(mvp);
}

// OpenGL Setup
void Model::Init()
{
	for (size_t i = 0; i < objects.size(); i++)// For every object
	{
		objects[i].Init();// Init it
	}
}

// To be run every game tick
void Model::Update()
{
	mvp = mvpBuilder.Build();// Re-create and use a new MVP. The MVP builder may have been adjusted between game ticks
	UseMVP(mvp);

	for (size_t i = 0; i < objects.size(); i++)// For every object
	{
		objects[i].Update();// Update it
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

	for (auto& pair : materials)// For every material in the materials map
	{
		results.push_back(pair.second);// Add it to a vector
	}

	return results;
}

MVPBuilder& Model::GetMVPBuilder()
{
	return mvpBuilder;
}

// Sets this Model's MVP as the current one in the shader program
void Model::UseMVP(mat4 mvp)
{
	int mvpLoc = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
}
