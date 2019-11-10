#pragma once

#include "Material.h"
#include "FileUtils.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
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
	glm::vec3& GetVector3(std::string& line);
};