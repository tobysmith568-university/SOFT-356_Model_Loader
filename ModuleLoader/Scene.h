#pragma once

#include "GL/glew.h"
#include "GLFWUtil.h"
#include "MVPBuilder.h"
#include "ConfigUtil.h"
#include "Model.h"
#include "InputManager.h"
#include "Texture.h"
#include "ConsoleUtil.h"
#include "ModelLoaderFactory.h"
#include "BasicModelLoader.h"

#include <glm/glm.hpp> //includes GLM
#include <vector>

class Scene
{
public:
	Scene(ConfigUtil& _configUtil, FileUtils& _fileUtils, InputManager& _inputManager,
		ConsoleUtil& _consoleUtil, ModelLoaderFactory& _modelLoaderFactory, BasicModelLoader& _basicModelLoader);
	void Update();

private:
	ConfigUtil configUtil;
	FileUtils fileUtils;
	InputManager& inputManager;
	ConsoleUtil consoleUtil;
	ModelLoaderFactory modelLoaderFactory;
	BasicModelLoader basicModelLoader;

	enum VAO_IDs { Vertices, Triangles, Colours, Tex };
	enum Buffer_IDs { ArrayBuffer };
	bool autoRotate;
	bool backfaceCull;

	std::vector<Model> models;
	GLuint activeModel;

	GLuint program;

	void SetGlobalState();
	void BindMovements();
	void BindBackgroundColours();
	float NormalizeColour(float colour);
	void CreateAndBindShaderProgram();
	void AddModel();
	void DeleteModel();
};