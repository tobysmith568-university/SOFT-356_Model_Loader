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
	backfaceCull = configUtil.GetBool(BoolSetting::BackfaceCull);// Get some config data
	autoRotate = configUtil.GetBool(BoolSetting::AutoRotate);

	try
	{
		SetGlobalState();
		BindMovements();
		CreateAndBindShaderProgram();
		BindBackgroundColours();
	}
	catch (exception ex)
	{
		consoleUtil.Print("\n\nThe scene could not be properly configured\n\n");
		consoleUtil.Print(ex.what());
		exit(-1);
	}
}

// To be run each game tick
void Scene::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Clears the previous buffers

	for (size_t i = 0; i < models.size(); i++)// For every model
	{
		if (autoRotate)// Rotate it if necessary
		{
			models[i].GetMVPBuilder()
				.AddRotation(0.005f, 0.0f, 1.0f, 0.0f);
		}

		models[i].Update();// Updated the model
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

	isWireframesOnly = configUtil.GetBool(BoolSetting::UseWireframes);
	UpdatePolygonMode();
}

// Binds the default clear colour for the scene
void Scene::BindBackgroundColours()
{
	float backgroundR = configUtil.GetFloat(FloatSetting::BackgroundR);// Read in the colour values from config
	float backgroundG = configUtil.GetFloat(FloatSetting::BackgroundG);
	float backgroundB = configUtil.GetFloat(FloatSetting::BackgroundB);
	float backgroundA = configUtil.GetFloat(FloatSetting::BackgroundA);

	backgroundR = NormalizeColour(backgroundR);// Set the colour values to be between 0 and 1
	backgroundG = NormalizeColour(backgroundG);
	backgroundB = NormalizeColour(backgroundB);
	backgroundA = NormalizeColour(backgroundA);

	glClearColor(backgroundR, backgroundG, backgroundB, backgroundA);// Set the background colours
}

// Normalizes an R, G, B, or A value
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
	string vertexShaderLocation = configUtil.GetString(StringSetting::VertexShader);// Get the shader loacations from config
	string fragmentShaderLocation = configUtil.GetString(StringSetting::FragmentShader);

	program = *ShaderProgramBuilder(fileUtils)// Create and use a shader program
		.AddVertexShader(vertexShaderLocation)
		.AddFragmentShader(fragmentShaderLocation)
		.BuildAndUse();
}

// Sets if only lines should be drawn or not
void Scene::UpdatePolygonMode()
{
	glPolygonMode(GL_FRONT_AND_BACK, isWireframesOnly ? GL_LINE : GL_FILL);
}

// Adds a new model to the scene from a file
void Scene::AddModel()
{
	consoleUtil.ClearConsole();
	string filename = consoleUtil.GetFileName("Enter a file name for a model");// Prompt for a model path

	try
	{
		IModelLoader& ml = modelLoaderFactory.GetLoaderForFile(filename);// Gets the correct model loader based on the paths .extension
		Model newModel = Model(program);
		ml.GetModel(newModel, filename, program);// Loads in model data using that model loader
		newModel.Init();// Inits the OpenGL code within the model
		models.push_back(newModel);
		activeModel = models.size() - 1;// Sets the model as the currently active model

	}
	catch (InvalidModelFileException& ex)
	{
		string message = ex.What();// Print to console any errors
		consoleUtil.Print(message);
	}
	catch (...)// Catch any additional errors
	{
		consoleUtil.Print("An unknown error occurred!");
	}
}

// Removes the most recently added model from the scene
void Scene::DeleteModel()
{
	if (models.size() > 0)// Removes the model from the back of the list
	{
		models.pop_back();
	}
}