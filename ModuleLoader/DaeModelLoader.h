#pragma once

#include <regex>

#include "IModelLoader.h"
#include "FileUtils.h"
#include "Input.h"
#include "Triangle.h"

class DaeModelLoader : public IModelLoader
{
public:
	DaeModelLoader(FileUtils& _fileUtils);
	void GetModel(Model& model, std::string fileLocation, GLuint& program);

private:
	FileUtils& fileUtils;

	void ParseSources(std::map<std::string, std::vector<GLfloat>>& sources, std::string fileData);
	void ParseVertices(std::map<std::string, std::vector<Input>>& vertices, std::string fileData);
	void ParseTriangles(std::vector<Triangle>& triangles, std::string fileData);

	void ReadInputs(std::vector<Input>& inputs, std::string inputData);
	void ReadInput(Input& input, std::smatch& match);
	void ReadIndices(std::vector<GLfloat> indices, std::string inputData);
	void ReadSpaceSepFloats(std::vector<GLfloat>& floats, std::string& line);
};