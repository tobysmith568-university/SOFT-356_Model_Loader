#pragma once

#include "IModelLoader.h"
#include "Model.h"
#include "FileUtils.h"

class BasicModelLoader : public IModelLoader
{
public:
	BasicModelLoader(FileUtils& _fileUtils);
	void Export(Model& model);
	void GetModel(Model& model, std::string fileLocation, GLuint& program);
	char* GetNextWord(char*& remaining);
	char* GetNextLine(char*& remaining);
	GLfloat GetNextWordAsFloat(char*& remaining);
	GLfloat GetNextLineAsFloat(char*& remaining);

private:
	FileUtils fileUtils;

	char space = ' ';
	char brokenBar = '¦';
	char bar = '|';
	char* empty = (char*)"";

	void GetTexture(Texture& texture, std::string& line, std::string& folder);
};