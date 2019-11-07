#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "FileUtils.h"
#include "IModelLoader.h"
#include "Model.h"

#include <iostream>

class BasicModelLoader : public IModelLoader
{
public:
	BasicModelLoader(FileUtils _fileUtils);
	Model& GetModel(std::string fileLocation);

private:
	FileUtils fileUtils;

	std::vector<GLfloat> GetFloatsFromSpacedSepString(std::string& spacesSepString, GLfloat maxValue);
	std::vector<GLuint> GetIntsFromSpacedSepString(std::string& spacesSepString, GLuint maxValue);
};