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

	std::vector<GLfloat> ReadVertices(std::string data);
	std::vector<GLfloat> ReadTextureCoords(std::string data);
	std::vector<GLfloat> ReadNormals(std::string data);
};