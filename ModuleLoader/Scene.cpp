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

#define BUFFER_OFFSET(a) ((void*)(a))

using namespace std;

Scene::Scene(ConfigUtil& _configUtil, FileUtils& _fileUtils, InputManager& _inputManager, Model& _model) 
			: configUtil(_configUtil), fileUtils(_fileUtils), inputManager(_inputManager), model(_model)
{
	BindMovements();
	CreateAndUseVAO();
	CreateAndBindShaderProgram();
	BindBackgroundColours();

	BindVertices(model.GetVertices());
	BindTriangles(model.GetTriangles());
	BindColours(model.GetColours());
	BindTextureCoords(model.GetTextureCoords());

	// load and create a texture 
	// -------------------------

	// texture 1
	// ---------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	GLint width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load("media/textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	glUniform1i(glGetUniformLocation(program, "texture1"), 0);

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

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_INT, 0);
}

void Scene::CreateAndUseVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
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

void Scene::BindVertices(const vector<GLfloat>& vertices)
{
	glGenBuffers(1, &vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
}

void Scene::BindTriangles(const vector<GLuint>& triangles)
{
	glGenBuffers(1, &triangleBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(GLuint), &triangles[0], GL_STATIC_DRAW);

	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
}

void Scene::BindColours(const vector<GLfloat>& colours)
{
	glGenBuffers(1, &colourBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glBufferStorage(GL_ARRAY_BUFFER, colours.size() * sizeof(GLfloat), &colours[0], 0);

	glVertexAttribPointer(cPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(cPosition);
}

void Scene::BindTextureCoords(const vector<GLfloat>& textureCoords)
{
	glGenBuffers(1, &textureBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(GLfloat), &textureCoords[0], GL_STATIC_DRAW);

	glVertexAttribPointer(tPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(tPosition);
}

void Scene::UseMVP(mat4 mvp)
{
	int mvpLoc = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
}