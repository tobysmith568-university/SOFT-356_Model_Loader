#pragma once

#include "GL/glew.h"
#include "GLFWUtil.h"
#include "MVPBuilder.h"
#include "ConfigUtil.h"
#include "Model.h"
#include "InputManager.h"

#include <glm/glm.hpp> //includes GLM
#include <vector>

class Scene
{
public:
	Scene(ConfigUtil& _configUtil, FileUtils& _fileUtils, InputManager& _inputManager, Model& _model);
	void Update();

private:
	ConfigUtil& configUtil;
	FileUtils& fileUtils;
	InputManager& inputManager;

	enum VAO_IDs { Vertices, Triangles, Colours, Tex };
	enum Buffer_IDs { ArrayBuffer };
	enum Attrib_IDs { vPosition = 0, cPosition = 1, tPosition = 2 };

	Model& model;
	
	GLuint VAO;
	GLuint vertexBuffer;
	GLuint triangleBuffer;
	GLuint colourBuffer;
	GLuint textureBuffer;
	GLuint texture1;

	GLuint program;

	const GLuint NumVertices = 36;

	MVPBuilder mvpBuilder;
	glm::mat4 mvp;

	void CreateAndUseVAO();
	void BindMovements();
	void BindBackgroundColours();
	float NormalizeColour(float colour);
	void CreateAndBindShaderProgram();
	void BindVertices(const std::vector<GLfloat>& vertices);
	void BindTriangles(const std::vector<GLuint>& triangles);
	void BindColours(const std::vector<GLfloat>& colours);
	void BindTextureCoords(const std::vector<GLfloat>& textureCoords);

	void UseMVP(mat4 mvp);
};