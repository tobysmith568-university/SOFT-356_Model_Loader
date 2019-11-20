#include "BasicModelLoader.h"

#include "Vertex.h"
#include "Base64.h"

#include <sstream>
#include <iostream>
#include <ctime>
#include "stb_image.h"

using namespace std;

BasicModelLoader::BasicModelLoader(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

void BasicModelLoader::Export(Model& model)
{
	ostringstream result;

	vector<Material> materials = model.GetMaterials();

	Material material;
	for (size_t i = 0; i < materials.size(); i++)
	{
		if (i != 0)
		{
			result << endl;
		}

		material = materials[i];

		result << material.name
			<< space << material.ambientColour.r
			<< space << material.ambientColour.g
			<< space << material.ambientColour.b
			<< space << material.diffuseColour.r
			<< space << material.diffuseColour.g
			<< space << material.diffuseColour.b
			<< space << material.specularColour.r
			<< space << material.specularColour.g
			<< space << material.specularColour.b
			<< space << material.specularColourWeight
			<< space << material.dissolve
			<< space << material.illuminationModel
			<< endl << (material.alphaTextureMap.GetPath().size() != 0 ? material.alphaTextureMap.GetPath() : "no.png")
			<< endl << (material.ambientTextureMap.GetPath().size() != 0 ? material.ambientTextureMap.GetPath() : "no.png")
			<< endl << (material.diffuseTextureMap.GetPath().size() != 0 ? material.diffuseTextureMap.GetPath() : "no.png");
	}

	vector<Object> objects = model.GetObjects();
	for (size_t i = 0; i < objects.size(); i++)
	{
		result << endl << endl << objects[i].GetName();

		vector<Mesh> meshes = objects[i].GetMeshes();
		for (size_t ii = 0; ii < meshes.size(); ii++)
		{
			Mesh& mesh = meshes[ii];
			result << endl << mesh.GetMaterial().name;
			
			vector<Vertex> vertices = mesh.GetVertices();
			vector<GLuint> indices = mesh.GetIndicies();

			for (size_t iii = 0; iii < indices.size(); iii++)
			{
				Vertex vertex = vertices[indices[iii]];

				result << space << vertex.position.x;
				result << space << vertex.position.y;
				result << space << vertex.position.z;
				result << space << vertex.normal.x;
				result << space << vertex.normal.y;
				result << space << vertex.normal.z;
				result << space << vertex.colour.r;
				result << space << vertex.colour.g;
				result << space << vertex.colour.b;
				result << space << vertex.colour.a;
				result << space << vertex.texture.x;
				result << space << vertex.texture.y;
			}
		}
	}

	string data = result.str();

	stringstream stringStream;
	stringStream << time(nullptr);
	string saveFileLocation = "C:/Exports/" + stringStream.str() + ".basic";

	fileUtils.SaveFile(data, saveFileLocation);
}

void BasicModelLoader::GetModel(Model& model, std::string fileLocation, GLuint& program)
{
	string folder = fileUtils.GetFolder(fileLocation);
	string fileData = fileUtils.ReadFile(fileLocation);

	vector<Vertex> vertices = vector<Vertex>();
	vector<GLuint> indices = vector<GLuint>();

	char* word = (char*)"";
	char* remaining = (char*)fileData.c_str();

	GLuint counter = 0;
	word = GetNextWord(remaining);

	while (word != "")
	{
		Material material = Material();
		material.name = word;
		material.ambientColour.r = GetNextWordAsFloat(remaining);
		material.ambientColour.g = GetNextWordAsFloat(remaining);
		material.ambientColour.b = GetNextWordAsFloat(remaining);
		material.diffuseColour.r = GetNextWordAsFloat(remaining);
		material.diffuseColour.g = GetNextWordAsFloat(remaining);
		material.diffuseColour.b = GetNextWordAsFloat(remaining);
		material.specularColour.r = GetNextWordAsFloat(remaining);
		material.specularColour.g = GetNextWordAsFloat(remaining);
		material.specularColour.b = GetNextWordAsFloat(remaining);
		material.specularColourWeight = GetNextWordAsFloat(remaining);
		material.dissolve = GetNextWordAsFloat(remaining);
		material.illuminationModel = GetNextLineAsFloat(remaining);

		string textureLine = GetNextLine(remaining);
		GetTexture(material.alphaTextureMap, textureLine, folder);

		textureLine = GetNextLine(remaining);
		GetTexture(material.ambientTextureMap, textureLine, folder);

		textureLine = GetNextLine(remaining);
		GetTexture(material.diffuseTextureMap, textureLine, folder);

		model.AddMaterial(material);
		word = remaining[0] == '\n' ? empty : GetNextWord(remaining);
	}

	word = GetNextLine(remaining);

	char* line = GetNextLine(remaining);
	Object* object = nullptr;
	Mesh* mesh = nullptr;

	object = new Object(program);
	string name = word;
	object->SetName(name);

	while (line != NULL)
	{
		mesh = new Mesh(program);
		vertices = vector<Vertex>();
		indices = vector<GLuint>();
		string materialName = GetNextWord(line);
		mesh->SetMaterial(model.GetMaterial(materialName));

		while (strcmp(line, "") != 0)
		{
			Vertex vertex = Vertex();

			vertex.SetPosition(
				GetNextWordAsFloat(line),
				GetNextWordAsFloat(line),
				GetNextWordAsFloat(line));

			vertex.SetNormal(
				GetNextWordAsFloat(line),
				GetNextWordAsFloat(line),
				GetNextWordAsFloat(line));

			vertex.SetColour(
				GetNextWordAsFloat(line),
				GetNextWordAsFloat(line),
				GetNextWordAsFloat(line),
				GetNextWordAsFloat(line));

			vertex.SetTexture(
				GetNextWordAsFloat(line),
				GetNextWordAsFloat(line));

			vertices.push_back(vertex);
			indices.push_back(counter);
			counter++;
		}

		mesh->SetIndicies(indices);
		mesh->SetVertices(vertices);

		object->AddMesh(*mesh);
		
		if (remaining[0] == '\n')
		{
			model.AddObject(*object);
			object = new Object(program);
			string name = GetNextLine(remaining);
			object->SetName(name);

		}
		line = GetNextLine(remaining);

		delete mesh;
	}

	model.AddObject(*object);
	delete object;
}

char* BasicModelLoader::GetNextWord(char*& remaining)
{
	return strtok_s(remaining, " ", &remaining);
}

char* BasicModelLoader::GetNextLine(char*& remaining)
{
	return strtok_s(remaining, "\n", &remaining);
}

GLfloat BasicModelLoader::GetNextWordAsFloat(char*& remaining)
{
	return stof(GetNextWord(remaining));
}

GLfloat BasicModelLoader::GetNextLineAsFloat(char*& remaining)
{
	return stof(GetNextLine(remaining));
}

void BasicModelLoader::GetTexture(Texture& texture, std::string& line, std::string& folder)
{
	string texturePath = folder + line;// Combine the line data with the current folder to form a path

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