#include "MtlLoader.h"

#include <vector>

using namespace std;

MtlLoader::MtlLoader(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

void MtlLoader::LoadMaterials(std::vector<Material>& materials, std::string& fileLocation)
{
	Material* material = nullptr;

	vector<string> fileLines = fileUtils.ReadFileAsLines(fileLocation);

	for (size_t i = 0; i < fileLines.size(); i++)
	{
		char* line = (char*)fileLines[i].c_str();
		if (strncmp(line, "newmtl ", 7) == 0)
		{
			if (material != nullptr)
			{
				materials.push_back(*material);
			}
			material = &Material();
			material->name = GetSingleString(fileLines[i]);
		}
		else if (strncmp(line, "Ns ", 3) == 0)
		{
			material->specularColourWeight = GetSingleFloat(fileLines[i]);
		}
		else if (strncmp(line, "Ka ", 3) == 0)
		{
			//	TODO
		}
		else if (strncmp(line, "Kd ", 3) == 0)
		{
			//	TODO
		}
		else if (strncmp(line, "Ks ", 3) == 0)
		{
			//	TODO
		}
		else if (strncmp(line, "Ke ", 3) == 0)
		{
			//	TODO
		}
		else if (strncmp(line, "d ", 2) == 0)
		{
			material->dissolve = GetSingleFloat(fileLines[i]);
		}
		else if (strncmp(line, "illum ", 6) == 0)
		{
			material->illuminationModel = GetSingleInt(fileLines[i]);
		}
		else if (strncmp(line, "map_Ka ", 7) == 0)
		{
			material->ambientTextureMap = GetSingleString(fileLines[i]);
		}
		else if (strncmp(line, "map_Kd ", 7) == 0)
		{
			material->diffuseTextureMap = GetSingleString(fileLines[i]);
		}
		else if (strncmp(line, "map_d ", 6) == 0)
		{
			material->alphaTextureMap = GetSingleString(fileLines[i]);
		}
	}

	if (material != nullptr)
	{
		materials.push_back(*material);
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