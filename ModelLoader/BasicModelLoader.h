#pragma once

#include "IModelLoader.h"
#include "Model.h"
#include "FileUtils.h"
#include "ConsoleUtil.h"

class BasicModelLoader : public IModelLoader
{
public:
	BasicModelLoader(FileUtils& _fileUtils, ConsoleUtil& _consoleUtil);
	void Export(Model& model);
	void GetModel(Model& model, std::string fileLocation, GLuint& program);
	char* GetNextWord(char*& remaining);
	char* GetNextLine(char*& remaining);
	GLfloat GetNextWordAsFloat(char*& remaining);
	GLfloat GetNextLineAsFloat(char*& remaining);

private:
	FileUtils fileUtils;
	ConsoleUtil consoleUtil;

	char space = ' ';
	char newLine = '\n';
	char* empty = (char*)"";
	std::string noPNG = "no.png";

	void GetTexture(Texture& texture, std::string& line, std::string& folder);
};