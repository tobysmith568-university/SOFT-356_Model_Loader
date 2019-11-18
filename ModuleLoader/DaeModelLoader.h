#pragma once

#include <regex>

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
	void ParseVertexInput(std::string& vertexID, std::string& vertexSource, std::string fileData);
	void ParseTriangleInputs(std::vector<Input>& inputs, std::string& material, std::string fileData);
	void ParseFaceData(std::vector<GLfloat>& faceData, std::string fileData);

	void ReadInputs(std::vector<Input>& inputs, std::string inputData);
	void ReadInput(Input& input, std::smatch& match);
	void ReadIndices(std::vector<GLfloat>& indices, std::string inputData);
	void ReadSpaceSepFloats(std::vector<GLfloat>& floats, std::string& line);

	void PairInputsAndSources(std::vector<Input>& inputs, std::map<std::string, std::vector<GLfloat>>& sources);

	void CreateVertices(std::vector<Vertex>& vertices, std::vector<Input>& inputs, std::vector<GLfloat>& indices);
};