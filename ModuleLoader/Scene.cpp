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
#include "InvalidModelFileException.h"

using namespace std;

Scene::Scene(ConfigUtil& _configUtil, FileUtils& _fileUtils, InputManager& _inputManager,
	ConsoleUtil& _consoleUtil, ModelLoaderFactory& _modelLoaderFactory, BasicModelLoader& _basicModelLoader)
			: configUtil(_configUtil), fileUtils(_fileUtils), inputManager(_inputManager),
	consoleUtil(_consoleUtil), modelLoaderFactory(_modelLoaderFactory), basicModelLoader(_basicModelLoader)
{
	backfaceCull = configUtil.GetBool(BoolSetting::BackfaceCull);
	autoRotate = configUtil.GetBool(BoolSetting::AutoRotate);

	SetGlobalState();
	BindMovements();
	CreateAndBindShaderProgram();
	BindBackgroundColours();
}

// To be run each tick
void Scene::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (size_t i = 0; i < models.size(); i++)
	{
		if (autoRotate)
		{
			models[i].GetMVPBuilder()
				.AddRotation(0.005f, 0.0f, 1.0f, 0.0f);
		}

		models[i].Update();// Updates all models in the scene
	}
}

// Sets any config for OpenGL
void Scene::SetGlobalState()
{
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	if (backfaceCull)
	{
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}
}

// Binds the default clear colour for the scene
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

// Mormalizes an R, G, B, or A value
float Scene::NormalizeColour(float colour)
{
	if (colour > 1)
	{
		colour /= 255;
	}

	return colour;
}

// Creates a shader program, links it, and uses it
void Scene::CreateAndBindShaderProgram()
{
	string vertexShaderLocation = configUtil.GetString(StringSetting::VertexShader);
	string fragmentShaderLocation = configUtil.GetString(StringSetting::FragmentShader);

	program = *ShaderProgramBuilder(fileUtils)
		.AddVertexShader(vertexShaderLocation)
		.AddFragmentShader(fragmentShaderLocation)
		.BuildAndUse();
}

// Adds a new model to the scene from a file
void Scene::AddModel()
{
	consoleUtil.ClearConsole();
	string filename = consoleUtil.GetFileName("Enter a file name for a model");

	try
	{
		IModelLoader& ml = modelLoaderFactory.GetLoaderForFile(filename);// Gets the correct model loader based on the paths .extension
		Model newModel = Model(program);
		ml.GetModel(newModel, filename, program);// Loads in model data using that model loader
		newModel.Init();
		models.push_back(newModel);
		activeModel = models.size() - 1;

	}
	catch (InvalidModelFileException& ex)
	{
		string message = ex.What();
		consoleUtil.Print(message);
	}

}

// Removes the most recently added model from the scene
void Scene::DeleteModel()
{
	if (models.size() > 0)
	{
		models.pop_back();
	}
}