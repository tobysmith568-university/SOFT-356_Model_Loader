#pragma once

#include "IModelLoader.h"
#include "FileUtils.h"
#include "Face.h"

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
	std::string indiciesRegex = "^f ([0-9]+)\\/([0-9]+)\\/([0-9]+) ([0-9]+)\\/([0-9]+)\\/([0-9]+) ([0-9]+)\\/([0-9]+)\\/([0-9]+)(?: ([0-9]+)\\/([0-9]+)\\/([0-9]+))?";

	void ReadVertex(std::vector<GLfloat>& vertices, std::string& line);
	std::vector<GLfloat> ReadTextureCoords(std::string data);
	std::vector<GLfloat> ReadNormals(std::string data);

	std::vector<Face> ReadIndicies(std::string& data);

	std::vector<GLfloat> ReadFloats(std::string& data, std::string& regexString);

	std::string GetTextureName(std::string& fileLocation);
	Texture LoadTexture(std::string textureLocation);
};