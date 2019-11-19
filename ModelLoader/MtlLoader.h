#pragma once

#include "Model.h"
#include "Material.h"
#include "FileUtils.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>
#include "stb_image.h"

class MtlLoader
{
public:
	MtlLoader(FileUtils& _fileUtils);

	void LoadMaterials(Model& model, std::string& fileLocation);

private:
	FileUtils fileUtils;

	char* GetSingleString(std::string& line);
	GLfloat GetSingleFloat(std::string& line);
	GLuint GetSingleInt(std::string& line);
	glm::vec3& GetVector3(std::string& line);
	void GetTexture(Texture& texture, std::string& line, std::string& folder);
};