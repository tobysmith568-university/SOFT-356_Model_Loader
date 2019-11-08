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
	
	static Model model;
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
