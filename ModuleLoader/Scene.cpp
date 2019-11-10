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

Scene::Scene(ConfigUtil& _configUtil, FileUtils& _fileUtils, InputManager& _inputManager, Model& _model) 
			: configUtil(_configUtil), fileUtils(_fileUtils), inputManager(_inputManager), model(_model)
{
	BindMovements();//Keeping
	//CreateAndUseVAO();//Moved
	CreateAndBindShaderProgram();//Keeping
	BindBackgroundColours();//Keeping

	//BindVertices(model.GetVertices());//Moved
	//BindIndices(model.GetIndicies());//Moved
	//BindTexture(model.GetTextures());// TODO!

	mvpBuilder = MVPBuilder()
		.AddScale(1.0f, 1.0f, 1.0f)
		.AddTranslation(0.0f, 0.0f, 0.0f);

	mvp = mvpBuilder.Build();
	UseMVP(mvp);
}

void Scene::Update()
{
	if (configUtil.GetBool(BoolSetting::AutoRotate))
	{
		mvpBuilder
			.AddRotation(0.005f, 0.0f, 1.0f, 0.0f);
	}

	mvp = mvpBuilder.Build();
	UseMVP(mvp);
	
	glClear(GL_COLOR_BUFFER_BIT);

	// bind textures on corresponding texture units
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

}

void Scene::BindMovements()
{
	inputManager.RegisterMapping(KeyBinding::RotateXPositive, [&]() {
		mvpBuilder.AddRotation(5.0f, 0.0f, 1.0f, 0.0f);
	});
	inputManager.RegisterMapping(KeyBinding::RotateXNegative, [&]() {
		mvpBuilder.AddRotation(-5.0f, 0.0f, 1.0f, 0.0f);
	});
	inputManager.RegisterMapping(KeyBinding::RotateYPositive, [&]() {
		mvpBuilder.AddRotation(5.0f, 1.0f, 0.0f, 0.0f);
	});
	inputManager.RegisterMapping(KeyBinding::RotateYNegative, [&]() {
		mvpBuilder.AddRotation(-5.0f, 1.0f, 0.0f, 0.0f);
	});
	inputManager.RegisterMapping(KeyBinding::ScaleUp, [&]() {
		mvpBuilder.AddScale(1.01f, 1.01f, 1.01f);
	});
	inputManager.RegisterMapping(KeyBinding::ScaleDown, [&]() {
		mvpBuilder.AddScale(0.99f, 0.99f, 0.99f);
	});
	inputManager.RegisterMapping(KeyBinding::Reset, [&]() {
		mvpBuilder = MVPBuilder();
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

void Scene::UseMVP(mat4 mvp)
{
	int mvpLoc = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
}