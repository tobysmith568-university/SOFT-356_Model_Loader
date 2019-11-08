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
	vector<GLfloat> vertices = vector<GLfloat>();
	const regex floatRegex("^v (-?[0-9]+\\.[0-9]+) (-?[0-9]+\\.[0-9]+) (-?[0-9]+\\.[0-9]+)");
	smatch sm;

	while (regex_search(data, sm, floatRegex)) {
		for (int i = 1; i < sm.size(); i++) {
			vertices.push_back(stof(sm[i]));
		}
		data = sm.suffix();
	}

	return vertices;
}

std::vector<GLfloat> ObjModelLoader::ReadTextureCoords(std::string data)
{
	vector<GLfloat> textureCoords = vector<GLfloat>();
	const regex floatRegex("^vt (-?[0-9]+\\.[0-9]+) (-?[0-9]+\\.[0-9]+)");
	smatch sm;

	while (regex_search(data, sm, floatRegex)) {
		for (int i = 1; i < sm.size(); i++) {
			textureCoords.push_back(stof(sm[i]));
		}
		data = sm.suffix();
	}

	return textureCoords;
}

std::vector<GLfloat> ObjModelLoader::ReadNormals(std::string data)
{
	vector<GLfloat> normals = vector<GLfloat>();
	const regex floatRegex("^vn (-?[01]\\.0+) (-?[01]\\.0+) (-?[01]\\.0+)");
	smatch sm;

	while (regex_search(data, sm, floatRegex)) {
		for (int i = 1; i < sm.size(); i++) {
			normals.push_back(stof(sm[i]));
		}
		data = sm.suffix();
	}

	return normals;
}