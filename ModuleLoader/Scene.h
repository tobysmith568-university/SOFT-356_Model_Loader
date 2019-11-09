#pragma once

#include "GL/glew.h"
#include "GLFWUtil.h"
#include "MVPBuilder.h"
#include "ConfigUtil.h"
#include "Model.h"
#include "InputManager.h"
#include "Texture.h"

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
	GLuint indicesBuffer;
	/*GLuint colourBuffer;
	GLuint textureCoordsBuffer;*/
	GLuint textureBuffer;

	GLuint program;

	MVPBuilder mvpBuilder;
	glm::mat4 mvp;

	void CreateAndUseVAO();
	void BindMovements();
	void BindBackgroundColours();
	float NormalizeColour(float colour);
	void CreateAndBindShaderProgram();
	void BindVertices(const std::vector<Vertex>& vertices);
	void BindIndices(const std::vector<GLuint>& indices);
	void BindTexture(std::vector<Texture> textures);

	void UseMVP(mat4 mvp);
};