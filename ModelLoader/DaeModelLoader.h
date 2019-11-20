#pragma once

#include <regex>

#include "IModelLoader.h"
#include "FileUtils.h"
#include "Input.h"
#include "Source.h"

class DaeModelLoader : public IModelLoader
{
public:
	DaeModelLoader(FileUtils& _fileUtils);
	void GetModel(Model& model, std::string fileLocation, GLuint& program);

private:
	FileUtils& fileUtils;

	void ParseSources(std::map<std::string, Source>& sources, std::string fileData);
	void ParseVertexInput(std::string& vertexID, std::string& vertexSource, std::string fileData);
	void ParseTriangleInputs(std::vector<Input>& inputs, std::string& material, std::string fileData);
	void ParseFaceData(std::vector<GLfloat>& faceData, std::string fileData);
	void ParseMaterial(Material& material, std::string fileData, std::string folder);

	void ReadInputs(std::vector<Input>& inputs, std::string inputData);
	void ReadInput(Input& input, std::smatch& match);
	void ReadSpaceSepFloats(std::vector<GLfloat>& floats, std::string& line);

	void PairInputsAndSources(std::vector<Input>& inputs, std::map<std::string, Source>& sources);

	void OrderInputsByOffset(std::vector<Input>& inputs);
	void CreateVertices(std::vector<Vertex>& vertices, std::vector<Input>& inputs, std::vector<GLfloat>& indices);

	void BuildModel(Model& model, Material material, std::vector<Vertex>& vertices, GLuint& program);
	void GetTexture(Texture& texture, std::string textureName, std::string texturePath);
};