#include "MtlLoader.h"

#include <vector>

using namespace std;
using namespace glm;

MtlLoader::MtlLoader(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

// Loads in a .mtl file and adds all the materials to the given Model
void MtlLoader::LoadMaterials(Model& model, std::string& fileLocation)
{
	Material* newMaterial = nullptr;

	std::string folder = fileUtils.GetFolder(fileLocation);
	vector<string> fileLines = fileUtils.ReadFileAsLines(fileLocation);// Read in the lines from the file

	for (size_t i = 0; i < fileLines.size(); i++)// For every line in the file, do different things based on what the line is prefixed with
	{
		char* line = (char*)fileLines[i].c_str();

		if (strncmp(line, "newmtl ", 7) == 0)// Creates a new material, adding the current one to the Model if there is one
		{
			if (newMaterial != nullptr)
			{
				model.AddMaterial(*newMaterial);
			}
			newMaterial = &Material();
			newMaterial->name = GetSingleString(fileLines[i]);
		}
		else if (newMaterial == nullptr)// If there is no current material, the following if-checks are redundant
		{
			continue;
		}
		else if (strncmp(line, "Ns ", 3) == 0)// Adds a specular colour weight
		{
			newMaterial->specularColourWeight = GetSingleFloat(fileLines[i]);
		}
		else if (strncmp(line, "Ka ", 3) == 0)// Adds an ambient colour
		{
			newMaterial->ambientColour = GetVector3(fileLines[i]);
		}
		else if (strncmp(line, "Kd ", 3) == 0)// Adds a diffuse colour
		{
			newMaterial->diffuseColour = GetVector3(fileLines[i]);
		}
		else if (strncmp(line, "Ks ", 3) == 0)// Adds a specular colour
		{
			newMaterial->specularColour = GetVector3(fileLines[i]);
		}
		else if (strncmp(line, "d ", 2) == 0)// Adds a disolve (opacity)
		{
			newMaterial->dissolve = GetSingleFloat(fileLines[i]);
		}
		else if (strncmp(line, "illum ", 6) == 0)// Adds the illumination model (0-10)
		{
			newMaterial->illuminationModel = GetSingleInt(fileLines[i]);
		}
		else if (strncmp(line, "map_Ka ", 7) == 0)// Adds an ambient texture
		{
			GetTexture(newMaterial->ambientTextureMap, fileLines[i], folder);
		}
		else if (strncmp(line, "map_Kd ", 7) == 0)// Adds a diffuse texture
		{
			GetTexture(newMaterial->diffuseTextureMap, fileLines[i], folder);
		}
		else if (strncmp(line, "map_d ", 6) == 0)// Adds an alpha (transparency) texture
		{
			GetTexture(newMaterial->alphaTextureMap, fileLines[i], folder);
		}
	}

	if (newMaterial != nullptr)// Adds the final material to the Model, assuming at least one was found
	{
		model.AddMaterial(*newMaterial);
	}
}

// Reads in a single string from the given data, minus the prefix
char* MtlLoader::GetSingleString(std::string& line)
{
	char* value;
	char* remaining;
	value = strtok_s((char*)line.c_str(), " ", &remaining);// Removes the prefix
	value = strtok_s(remaining, " ", &remaining);

	return value;
}

// Loads in a single float from the given data, minus the prefix
GLfloat MtlLoader::GetSingleFloat(std::string& line)
{
	return stof(GetSingleString(line));
}

// Loads in a single integer from the given data, minus the prefix
GLuint MtlLoader::GetSingleInt(std::string& line)
{
	return stoi(GetSingleString(line));
}

// Loads in a single vector3 from the given data based on 3 space separated values
glm::vec3& MtlLoader::GetVector3(std::string& line)
{
	GLuint value = 0;

	vec3 newVec3 = vec3();

	char* word;
	char* remaining;
	word = strtok_s((char*)line.c_str(), " ", &remaining);// Removes the prefix
	word = strtok_s(remaining, " ", &remaining);
	while (word != NULL)
	{
		if (value == 0)// Read a value into the X, then Y, and Z
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
		word = strtok_s(remaining, " ", &remaining);// Read the next 'word'
	}

	return newVec3;
}

void MtlLoader::GetTexture(Texture& texture, std::string& line, std::string& folder)
{
	string textureName = GetSingleString(line);
	string texturePath = folder + textureName;// Combine the line data with the current folder to form a path

	GLint width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* c_data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);// Read in the texture file

	if (!c_data)
	{
		//TODO Error handling
	}

	texture.SetPath(texturePath);
	texture.SetWidth(width);
	texture.SetHeight(height);
	texture.SetNrChannels(nrChannels);
	texture.SetData(c_data);
}