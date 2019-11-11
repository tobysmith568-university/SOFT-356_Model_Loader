#include "Scene.h"
#include "ShaderProgramBuilder.h"

#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <cstddef>
#include <iostream>
#include <functional>

using namespace std;

Scene::Scene(ConfigUtil& _configUtil, FileUtils& _fileUtils, InputManager& _inputManager, ConsoleUtil& _consoleUtil, ModelLoaderFactory& _modelLoaderFactory)
			: configUtil(_configUtil), fileUtils(_fileUtils), inputManager(_inputManager), consoleUtil(_consoleUtil), modelLoaderFactory(_modelLoaderFactory)
{
	BindMovements();
	CreateAndBindShaderProgram();
	BindBackgroundColours();

	autoRotate = configUtil.GetBool(BoolSetting::AutoRotate);
}

void Scene::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (size_t i = 0; i < models.size(); i++)
	{
		if (autoRotate)
		{
			models[i].GetMVPBuilder()
				.AddRotation(0.005f, 0.0f, 1.0f, 0.0f);
		}

		models[i].Update();
	}
	

	// bind textures on corresponding texture units
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void Scene::BindMovements()
{
	inputManager.RegisterKeyPress(KeyBinding::RotateXPositive, [&]() {
		models[models.size() - 1].GetMVPBuilder().AddRotation(5.0f, 0.0f, 1.0f, 0.0f);
	});
	inputManager.RegisterKeyPress(KeyBinding::RotateXNegative, [&]() {
		models[models.size() - 1].GetMVPBuilder().AddRotation(-5.0f, 0.0f, 1.0f, 0.0f);
	});
	inputManager.RegisterKeyPress(KeyBinding::RotateYPositive, [&]() {
		models[models.size() - 1].GetMVPBuilder().AddRotation(5.0f, 1.0f, 0.0f, 0.0f);
	});
	inputManager.RegisterKeyPress(KeyBinding::RotateYNegative, [&]() {
		models[models.size() - 1].GetMVPBuilder().AddRotation(-5.0f, 1.0f, 0.0f, 0.0f);
	});
	inputManager.RegisterKeyPress(KeyBinding::ScaleUp, [&]() {
		models[models.size() - 1].GetMVPBuilder().AddScale(1.01f, 1.01f, 1.01f);
	});
	inputManager.RegisterKeyPress(KeyBinding::ScaleDown, [&]() {
		models[models.size() - 1].GetMVPBuilder().AddScale(0.99f, 0.99f, 0.99f);
	});
	inputManager.RegisterKeyPress(KeyBinding::NewModel, [&]() {
		AddModel();
	});
	inputManager.RegisterKeyPress(KeyBinding::Reset, [&]() {
		for (size_t i = 0; i < models.size(); i++)
		{
			models[i].GetMVPBuilder() = MVPBuilder();
		}
	});
}

void Scene::BindBackgroundColours()
{
	float backgroundR = configUtil.GetFloat(FloatSetting::BackgroundR);
	float backgroundG = configUtil.GetFloat(FloatSetting::BackgroundG);
	float backgroundB = configUtil.GetFloat(FloatSetting::BackgroundB);
	float backgroundA = configUtil.GetFloat(FloatSetting::BackgroundA);

	backgroundR = NormalizeColour(backgroundR);
	backgroundG = NormalizeColour(backgroundG);
	backgroundB = NormalizeColour(backgroundB);
	backgroundA = NormalizeColour(backgroundA);

	glClearColor(backgroundR, backgroundG, backgroundB, backgroundA);
}

float Scene::NormalizeColour(float colour)
{
	if (colour > 1)
	{
		colour /= 255;
	}

	return colour;
}

void Scene::CreateAndBindShaderProgram()
{
	string vertexShaderLocation = configUtil.GetString(StringSetting::VertexShader);
	string fragmentShaderLocation = configUtil.GetString(StringSetting::FragmentShader);

	program = *ShaderProgramBuilder(fileUtils)
		.AddVertexShader(vertexShaderLocation)
		.AddFragmentShader(fragmentShaderLocation)
		.BuildAndUse();
}

void Scene::AddModel()
{
	string filename = consoleUtil.GetFileName("Enter a file name for a model");
	IModelLoader& ml = modelLoaderFactory.GetLoaderForFile(filename);
	models.push_back(Model(program));
	ml.GetModel(models[models.size() - 1], filename, program);
	models[models.size() - 1].Init();
}
