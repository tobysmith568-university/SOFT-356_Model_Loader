#pragma once

#include "Object.h"
#include "GLFW/glfw3.h"

#include "Texture.h"
#include "Vertex.h"
#include "Material.h"

#include <vector>
#include <map>

#include "Mesh.h"
#include "MVPBuilder.h"

class Model
{
public:
	Model(GLuint& _program);
	void Init();
	void Update();

	void AddObject(Object& object);
	std::vector<Object>& GetObjects();

	void AddMaterial(Material& material);
	Material& GetMaterial(std::string& name);
	std::vector<Material> GetMaterials();

	MVPBuilder& GetMVPBuilder();

private:
	void UseMVP(mat4 mvp);

	GLuint& program;

	std::vector<Object> objects;
	std::map<std::string, Material> materials;

	MVPBuilder mvpBuilder;
	glm::mat4 mvp;
};