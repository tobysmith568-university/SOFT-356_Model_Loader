#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "FileUtils.h"
#include "IModelLoader.h"
#include "Model.h"

#include <iostream>
#include "ConsoleUtil.h"

class BasicModelLoader : public IModelLoader
{
public:
	BasicModelLoader(FileUtils _fileUtils, ConsoleUtil _consoleUtil);
	Model& GetModel(std::string fileLocation);

private:
	FileUtils fileUtils;
	ConsoleUtil consoleUtil;

	char dot = '.';
	std::vector<std::string> textureExtentions = {
		"jpg",
		"png"
	};

	std::vector<GLfloat> GetFloatsFromSpacedSepString(std::string& spacesSepString, GLfloat maxValue);
	std::vector<GLuint> GetIntsFromSpacedSepString(std::string& spacesSepString, GLuint maxValue);
	std::string GetTextureName(std::string& fileLocation);
	Texture LoadTexture(std::string textureLocation);
};