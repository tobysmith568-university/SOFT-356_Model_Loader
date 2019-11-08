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