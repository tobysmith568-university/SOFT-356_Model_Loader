#include "ObjModelLoader.h"
#include "Vertex.h"
#include "stb_image.h"

using namespace std;

ObjModelLoader::ObjModelLoader(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

Model& ObjModelLoader::GetModel(std::string fileLocation)
{
	vector<GLfloat> vertexValues = vector<GLfloat>();
	vector<GLfloat> textureCoordValues = vector<GLfloat>();
	vector<GLfloat> normalValues = vector<GLfloat>();
	vector<Face> faceValues = vector<Face>();

	vector<string> fileLines = fileUtils.ReadFileAsLines(fileLocation);

	for (size_t i = 0; i < fileLines.size(); i++)
	{
		char* line = (char*)fileLines[i].c_str();
		if (strncmp(line, "v ", 2) == 0)
		{
			ReadSpaceSepFloats(vertexValues, fileLines[i]);
		}
		else if (strncmp(line, "vt ", 3) == 0)
		{
			ReadSpaceSepFloats(textureCoordValues, fileLines[i]);
		}
		else if (strncmp(line, "vn ", 3) == 0)
		{
			ReadSpaceSepFloats(normalValues, fileLines[i]);
		}
		else if (strncmp(line, "f ", 2) == 0)
		{
			ReadFace(faceValues, fileLines[i]);
		}
	}

	static Model model;
	SetVertices(model, vertexValues, textureCoordValues, normalValues, faceValues);
	SetIndices(model, faceValues);
	SetTextures(model, fileLocation);
	return model;
}

void ObjModelLoader::ReadSpaceSepFloats(vector<GLfloat>& values, string& line)
{
	char* word;
	char* remaining;
	word = strtok_s((char*)line.c_str(), " ", &remaining);
	word = strtok_s(remaining, " ", &remaining);
	while (word != NULL)
	{
		values.push_back(stof(word));
		word = strtok_s(remaining, " ", &remaining);
	}
}

void ObjModelLoader::ReadFace(std::vector<Face>& faces, std::string& line)
{
	Face face = Face();

	char* word;
	char* remaining;
	word = strtok_s((char*)line.c_str(), " ", &remaining);
	word = strtok_s(remaining, " ", &remaining);
	while (word != NULL)// For each group of numbers
	{
		ReadIndex(face, word);
		word = strtok_s(remaining, " ", &remaining);
	}

	faces.push_back(face);
}

void ObjModelLoader::ReadIndex(Face& face, char* index)
{
	GLuint value = 0;

	Index newIndex = Index();

	char* word;
	char* remaining;
	word = strtok_s(index, "/", &remaining);
	while (word != NULL)// For each number
	{
		if (value == 0)
		{
			newIndex.vertexIndex = stoi(word);
		}
		else if (value == 1)
		{
			newIndex.textureIndex = stoi(word);
		}
		else if (value == 2)
		{
			newIndex.normalIndex = stoi(word);
		}

		value++;
		word = strtok_s(remaining, "/", &remaining);
	}

	face.AddIndex(newIndex);
}

void ObjModelLoader::SetVertices(Model& model,
	vector<GLfloat>& vertexValues,
	vector<GLfloat>& textureCoordValues,
	vector<GLfloat>& normalValues,
	vector<Face>& faceValues)
{
	vector<Vertex> vertices = vector<Vertex>();

	for (size_t i = 0; i < faceValues.size(); i++)//	For every face
	{
		vector<Index> indices = faceValues[i].GetIndices();

		for (size_t ii = 0; ii < indices.size(); ii++)// For every index
		{
			Vertex vertex = Vertex();

			GLuint vertexValue = ((indices[ii].vertexIndex - 1) * 3);
			GLuint textureValue = ((indices[ii].textureIndex - 1) * 2);
			GLuint normalValue = ((indices[ii].normalIndex - 1) * 3);

			vertex.SetPosition(
				vertexValues[vertexValue + 0],
				vertexValues[vertexValue + 1],
				vertexValues[vertexValue + 2]);

			vertex.SetTexture(
				textureCoordValues[textureValue + 0],
				textureCoordValues[textureValue + 1]);

			vertex.SetNormal(
				normalValues[normalValue + 0],
				normalValues[normalValue + 1],
				normalValues[normalValue + 2]);

			vertices.push_back(vertex);
		}
	}

	model.SetVertices(vertices);
}

void ObjModelLoader::SetIndices(Model& model, vector<Face>& faces)
{
	vector<GLuint> indices = vector<GLuint>();

	GLuint offset = 0;
	for (size_t i = 0; i < faces.size(); i++)
	{
		offset = faces[i].GetOffset(indices, offset);
	}

	model.SetIndicies(indices);
}

void ObjModelLoader::SetTextures(Model& model, std::string& fileLocation)
{
	string textureLocation = GetTextureName(fileLocation);
	if (textureLocation != "")
	{
		Texture texture = LoadTexture(textureLocation);
		vector<Texture> textures = vector<Texture>
		{
			texture
		};

		model.SetTextures(textures);
	}
}

std::string ObjModelLoader::GetTextureName(std::string& fileLocation)
{
	return "media/Texture.png";
}

Texture ObjModelLoader::LoadTexture(std::string textureLocation)
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