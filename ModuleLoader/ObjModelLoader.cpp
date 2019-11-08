#include "ObjModelLoader.h"

using namespace std;

ObjModelLoader::ObjModelLoader(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

Model& ObjModelLoader::GetModel(std::string fileLocation)
{
	string fileContent = fileUtils.ReadFile(fileLocation);

	vector<GLfloat> vertices = ReadVertices(fileContent);
	vector<GLfloat> textureCoords = ReadTextureCoords(fileContent);
	vector<GLfloat> normals = ReadNormals(fileContent);
	
	vector<GLuint> vertexIndices = ReadVertexIndicies(fileContent);
	
	static Model model;
	model.SetVertices(vertices);
	model.SetTriangles(vertexIndices);
	return model;
}

std::vector<GLfloat> ObjModelLoader::ReadVertices(std::string data)
{
	return ReadFloats(data, verticesRegex);
}

std::vector<GLfloat> ObjModelLoader::ReadTextureCoords(std::string data)
{
	return ReadFloats(data, textureCoordsRegex);
}

std::vector<GLfloat> ObjModelLoader::ReadNormals(std::string data)
{
	return ReadFloats(data, normalRegex);
}

std::vector<GLuint> ObjModelLoader::ReadVertexIndicies(std::string data)
{
	return ReadIndicies(data, indiciesRegex);
}

std::vector<GLfloat> ObjModelLoader::ReadFloats(std::string& data, std::string& regexString)
{
	vector<GLfloat> floats = vector<GLfloat>();
	const regex floatRegex(regexString);
	smatch sm;

	while (regex_search(data, sm, floatRegex))
	{
		for (int i = 1; i < sm.size(); i++)
		{
			floats.push_back(stof(sm[i]));
		}
		data = sm.suffix();
	}

	return floats;
}

//	Only supports 3 or 4 indicies per line
std::vector<GLuint> ObjModelLoader::ReadIndicies(std::string& data, std::string& regexString)
{
	vector<GLuint> ints = vector<GLuint>();
	const regex intRegex(regexString);
	smatch sm;

	while (regex_search(data, sm, intRegex))
	{
		vector<GLuint> rowOfIndices = vector<GLuint>();

		for (int i = 1; i < sm.size(); i++)
		{
			rowOfIndices.push_back(stoi(sm[i]));
		}

		if (rowOfIndices.size() == 3)
		{
			ints.push_back(rowOfIndices[0] - 1);
			ints.push_back(rowOfIndices[1] - 1);
			ints.push_back(rowOfIndices[2] - 1);
		}								   
		else							   
		{								   
			ints.push_back(rowOfIndices[0] - 1);
			ints.push_back(rowOfIndices[1] - 1);
			ints.push_back(rowOfIndices[2] - 1);
			ints.push_back(rowOfIndices[0] - 1);
			ints.push_back(rowOfIndices[2] - 1);
			ints.push_back(rowOfIndices[3] - 1);
		}

		data = sm.suffix();
	}

	return ints;
}