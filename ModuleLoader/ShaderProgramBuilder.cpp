#include "ShaderProgramBuilder.h"

using namespace std;

ShaderProgramBuilder::ShaderProgramBuilder(FileUtils& _fileUtils) : fileUtils(_fileUtils)
{
	program = glCreateProgram();
}

ShaderProgramBuilder& ShaderProgramBuilder::AddVertexShader(string fileLocation)
{
	AddShader(fileLocation, GL_VERTEX_SHADER);
	return *this;
}

ShaderProgramBuilder& ShaderProgramBuilder::AddFragmentShader(string fileLocation)
{
	AddShader(fileLocation, GL_FRAGMENT_SHADER);
	return *this;
}

GLuint* ShaderProgramBuilder::BuildAndUse()
{
	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		//TODO: Error checking
	}

	glUseProgram(program);

	return &program;
}

void ShaderProgramBuilder::AddShader(string fileLocation, int shaderType)
{
	string source = fileUtils.ReadFile(&fileLocation[0]);
	const GLchar* c_source = source.c_str();

	//TODO: Error checking

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &c_source, NULL);

	glCompileShader(shader);

	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		//TODO: Error checking
	}

	glAttachShader(program, shader);
}