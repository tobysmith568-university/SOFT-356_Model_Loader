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

#include <glm/glm.hpp>
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

	bool autoRotate;
	bool backfaceCull;
	bool isWireframesOnly;

	std::vector<Model> models;
	GLuint activeModel;

	GLuint program;

	void SetGlobalState();
	void BindMovements();
	void BindBackgroundColours();
	float NormalizeColour(float colour);
	void CreateAndBindShaderProgram();
	void UpdatePolygonMode();
	void AddModel();
	void DeleteModel();
};