#pragma once

#include "GL/glew.h"
#include "FileUtils.h"

class ShaderProgramBuilder
{
public:
	ShaderProgramBuilder(FileUtils& _fileUtils);
	ShaderProgramBuilder& AddVertexShader(std::string fileLocation);
	ShaderProgramBuilder& AddFragmentShader(std::string fileLocation);
	GLuint* BuildAndUse();
private:
	GLuint program;
	FileUtils fileUtils;

	void AddShader(std::string fileLocation, int shaderType);
};