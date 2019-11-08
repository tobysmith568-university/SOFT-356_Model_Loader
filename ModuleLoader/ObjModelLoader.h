#pragma once

#include "IModelLoader.h"
#include "FileUtils.h"
#include <regex>

class ObjModelLoader : public IModelLoader
{
public:
	ObjModelLoader(FileUtils& fileUtils);
	Model& GetModel(std::string fileLocation);

private:
	FileUtils fileUtils;

	std::string verticesRegex = "^v (-?[0-9]+\\.[0-9]+) (-?[0-9]+\\.[0-9]+) (-?[0-9]+\\.[0-9]+)";
	std::string textureCoordsRegex = "^vt (-?[0-9]+\\.[0-9]+) (-?[0-9]+\\.[0-9]+)";
	std::string normalRegex = "^vn (-?[01]\\.0+) (-?[01]\\.0+) (-?[01]\\.0+)";
	std::string indiciesRegex = "^f ([0-9]+).*? ([0-9]+).*? ([0-9]+)(?:.*? ([0-9]+))?";

	std::vector<GLfloat> ReadVertices(std::string data);
	std::vector<GLfloat> ReadTextureCoords(std::string data);
	std::vector<GLfloat> ReadNormals(std::string data);
	std::vector<GLuint> ReadVertexIndicies(std::string data);

	std::vector<GLfloat> ReadFloats(std::string& data, std::string& regexString);
	std::vector<GLuint> ReadIndicies(std::string& data, std::string& regexString);
};