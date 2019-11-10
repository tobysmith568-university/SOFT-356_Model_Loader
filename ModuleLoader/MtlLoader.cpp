#include "MtlLoader.h"

#include <vector>

using namespace std;
using namespace glm;

MtlLoader::MtlLoader(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

void MtlLoader::LoadMaterials(std::vector<Material>& materials, std::string& fileLocation)
{
	GLint currentMaterial = materials.size() - 1;

	vector<string> fileLines = fileUtils.ReadFileAsLines(fileLocation);

	for (size_t i = 0; i < fileLines.size(); i++)
	{
		char* line = (char*)fileLines[i].c_str();

		if (strncmp(line, "newmtl ", 7) == 0)
		{
			materials.push_back(Material());
			currentMaterial = materials.size() - 1;
			materials[currentMaterial].name = GetSingleString(fileLines[i]);
		}
		else if (currentMaterial < 0)
		{
			continue;
		}
		else if (strncmp(line, "Ns ", 3) == 0)
		{
			materials[currentMaterial].specularColourWeight = GetSingleFloat(fileLines[i]);
		}
		else if (strncmp(line, "Ka ", 3) == 0)
		{
			materials[currentMaterial].ambientColour = GetVector3(fileLines[i]);
		}
		else if (strncmp(line, "Kd ", 3) == 0)
		{
			materials[currentMaterial].diffuseColour = GetVector3(fileLines[i]);
		}
		else if (strncmp(line, "Ks ", 3) == 0)
		{
			materials[currentMaterial].specularColour = GetVector3(fileLines[i]);
		}
		else if (strncmp(line, "d ", 2) == 0)
		{
			materials[currentMaterial].dissolve = GetSingleFloat(fileLines[i]);
		}
		else if (strncmp(line, "illum ", 6) == 0)
		{
			materials[currentMaterial].illuminationModel = GetSingleInt(fileLines[i]);
		}
		else if (strncmp(line, "map_Ka ", 7) == 0)
		{
			materials[currentMaterial].ambientTextureMap = GetSingleString(fileLines[i]);
		}
		else if (strncmp(line, "map_Kd ", 7) == 0)
		{
			materials[currentMaterial].diffuseTextureMap = GetSingleString(fileLines[i]);
		}
		else if (strncmp(line, "map_d ", 6) == 0)
		{
			materials[currentMaterial].alphaTextureMap = GetSingleString(fileLines[i]);
		}
	}
}

char* MtlLoader::GetSingleString(std::string& line)
{
	char* value;
	char* remaining;
	value = strtok_s((char*)line.c_str(), " ", &remaining);
	value = strtok_s(remaining, " ", &remaining);

	return value;
}

GLfloat MtlLoader::GetSingleFloat(std::string& line)
{
	return stof(GetSingleString(line));
}

GLuint MtlLoader::GetSingleInt(std::string& line)
{
	return stoi(GetSingleString(line));
}

glm::vec3& MtlLoader::GetVector3(std::string& line)
{
	GLuint value = 0;

	vec3 newVec3 = vec3();

	char* word;
	char* remaining;
	word = strtok_s((char*)line.c_str(), " ", &remaining);
	word = strtok_s(remaining, " ", &remaining);
	while (word != NULL)
	{
		if (value == 0)
		{
			newVec3.x = stof(word);
		}
		else if (value == 1)
		{
			newVec3.y = stof(word);
		}
		else if (value == 2)
		{
			newVec3.z = stof(word);
		}

		value++;
		word = strtok_s(remaining, " ", &remaining);
	}

	return newVec3;
}