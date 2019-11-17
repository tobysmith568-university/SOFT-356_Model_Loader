#pragma once

#include "IModelLoader.h"
#include "FileUtils.h"
#include "Input.h"

class DaeModelLoader : public IModelLoader
{
public:
	DaeModelLoader(FileUtils& _fileUtils);
	void GetModel(Model& model, std::string fileLocation, GLuint& program);

private:
	FileUtils& fileUtils;

	void ParseSources(std::map<std::string, std::vector<GLfloat>>& sources, std::string fileData);
	void ParseVertices(std::map<std::string, std::vector<Input>>& vertices, std::string fileData);

	void ReadInputs(std::vector<Input>& inputs, std::string inputData);
	void ReadSpaceSepFloats(std::vector<GLfloat>& floats, std::string& line);
};