#pragma once

#include "Material.h"
#include "FileUtils.h"

#include <string>

class MtlLoader
{
public:
	MtlLoader(FileUtils& _fileUtils);

	void LoadMaterials(std::vector<Material>& materials, std::string& fileLocation);

private:
	FileUtils fileUtils;

	char* GetSingleString(std::string& line);
	GLfloat GetSingleFloat(std::string& line);
	GLuint GetSingleInt(std::string& line);
};