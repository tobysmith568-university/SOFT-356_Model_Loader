#include "BasicModelLoader.h"
#include "InvalidModelFileException.h"

#include <sstream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <limits>

#include "stb_image.h"

using namespace std;

BasicModelLoader::BasicModelLoader(FileUtils _fileUtils, ConsoleUtil _consoleUtil)
								 : fileUtils(_fileUtils), consoleUtil(_consoleUtil)
{
}

Model& BasicModelLoader::GetModel(string fileLocation)
{
	vector<string> lines = fileUtils.ReadFileAsLines(fileLocation.c_str());

	if (lines.size() != 4)
	{
		throw InvalidModelFileException(fileLocation.c_str(), "The given file is not exactly 4 lines long");
	}

	static Model model;

	try
	{/*
		model.SetVertices(GetFloatsFromSpacedSepString(lines[0], numeric_limits<GLfloat>::max()));
		model.SetTriangles(GetIntsFromSpacedSepString(lines[1], model.GetVertices().size()));
		model.SetColours(GetFloatsFromSpacedSepString(lines[2], 1.0f));
		model.SetTextureCoords(GetFloatsFromSpacedSepString(lines[3], 1.0f));*/
	}
	catch (const std::runtime_error& ex)
	{
		throw InvalidModelFileException(fileLocation.c_str(), ex);
	}

	string textureLocation = GetTextureName(fileLocation);

	if (textureLocation != "")
	{
		Texture texture = LoadTexture(textureLocation);
		vector<Texture> textures = vector<Texture>
		{
			texture
		};

		//model.SetTextures(textures);
	}

	return model;
}

std::vector<GLfloat> BasicModelLoader::GetFloatsFromSpacedSepString(std::string& spacesSepString, GLfloat maxValue)
{
	std::vector<GLfloat> results = std::vector<GLfloat>();

	std::stringstream stream(spacesSepString);

	std::string currentString;
	GLfloat currentFloat;
	while (getline(stream, currentString, ' '))
	{
		currentFloat = stof(currentString);

		if (currentFloat > maxValue)
		{
			throw out_of_range("The value [" + currentString + "] is too high");
		}

		results.push_back(currentFloat);
	}

	return results;
}

std::vector<GLuint> BasicModelLoader::GetIntsFromSpacedSepString(std::string& spacesSepString, GLuint maxValue)
{
	std::vector<GLuint> results = std::vector<GLuint>();

	std::stringstream stream(spacesSepString);

	std::string currentString;
	GLuint currentInt;
	while (getline(stream, currentString, ' '))
	{
		currentInt = stoi(currentString);

		if (currentInt > maxValue)
		{
			throw out_of_range("The value [" + currentString + "] is too high");
		}

		results.push_back(currentInt);
	}

	return results;
}

std::string BasicModelLoader::GetTextureName(string& fileLocation)
{
	string baseFileName = fileUtils.GetName(fileLocation);

	for (size_t i = 0; i < textureExtentions.size(); i++)
	{
		string textureLocationToTest = baseFileName + dot + textureExtentions[i];
		if (fileUtils.DoesFileExist(textureLocationToTest))
		{
			return textureLocationToTest;
		}
	}

	return consoleUtil.GetInput("Could not automatically detect a texture, enter texture location");
}

Texture BasicModelLoader::LoadTexture(std::string textureLocation)
{
	GLint width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(textureLocation.c_str(), &width, &height, &nrChannels, 0);

	if (!data)
	{
		//TODO Error handling
	}

	Texture texture = Texture(width, height, nrChannels, data);
	return texture;
}
