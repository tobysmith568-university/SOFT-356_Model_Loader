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
	string fileContent = fileUtils.ReadFile(fileLocation);

	vector<GLfloat> vertexValues = ReadVertices(fileContent);
	vector<GLfloat> textureCoordValues = ReadTextureCoords(fileContent);
	vector<GLfloat> normalValues = ReadNormals(fileContent);

	vector<Face> faces = ReadIndicies(fileContent);

	vector<Vertex> vertices = vector<Vertex>();

	for (size_t i = 0; i < faces.size(); i++)//	For every face
	{
		vector<Index> indices = faces[i].GetIndices();

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

	vector<GLuint> indices = vector<GLuint>();

	GLuint offset = 0;
	for (size_t i = 0; i < faces.size(); i++)
	{
		offset = faces[i].GetOffset(indices, offset);
	}

	static Model model;
	model.SetVertices(vertices);
	model.SetIndicies(indices);

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

	return model;
}

std::vector<GLfloat> ObjModelLoader::ReadVertices(std::string data)
{
	return ReadFloats(data, verticesRegex);
}

std::vector<GLfloat> ObjModelLoader::ReadTextureCoords(std::string data)
{
	return ReadFloats(data, textureCoordsRegex);
}

std::vector<GLfloat> ObjModelLoader::ReadNormals(std::string data)
{
	return ReadFloats(data, normalRegex);
}

std::vector<Face> ObjModelLoader::ReadIndicies(std::string& data)
{
	vector<Face> faces = vector<Face>();

	vector<GLuint> ints = vector<GLuint>();
	const regex floatRegex(indiciesRegex);
	smatch sm;

	while (regex_search(data, sm, floatRegex))//For each line
	{
		Face face = Face();
		for (int i = 1; i < sm.size(); i = i + 3)//For each 3 groups
		{
			if (!sm[i].matched || !sm[i + 1].matched || !sm[i + 2].matched)
			{
				continue;
			}

			Index index = Index(stoi(sm[i]), stoi(sm[i + 1]), stoi(sm[i + 2]));
			face.AddIndex(index);
		}

		faces.push_back(face);

		data = sm.suffix();
	}

	return faces;
}

std::vector<GLfloat> ObjModelLoader::ReadFloats(std::string& data, std::string& regexString)
{
	vector<GLfloat> floats = vector<GLfloat>();
	const regex floatRegex(regexString);
	smatch sm;

	while (regex_search(data, sm, floatRegex))
	{
		for (int i = 1; i < sm.size(); i++)
		{
			floats.push_back(stof(sm[i]));
		}
		data = sm.suffix();
	}

	return floats;
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