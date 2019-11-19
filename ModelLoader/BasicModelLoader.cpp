#include "BasicModelLoader.h"

#include "Vertex.h"
#include "Base64.h"

#include <sstream>
#include <iostream>
#include <ctime>

using namespace std;

BasicModelLoader::BasicModelLoader(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

void BasicModelLoader::Export(Model& model)
{
	/*ostringstream result;

	vector<Material> materials = model.GetMaterials();

	Material material;
	for (size_t i = 0; i < materials.size(); i++)
	{
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

			<< endl << material.alphaTextureMap.GetWidth()
			<< space << material.alphaTextureMap.GetHeight()
			<< space << material.alphaTextureMap.GetNrChannels()
			<< space << base64_encode((const unsigned char*)material.alphaTextureMap.GetData().c_str(), strlen(material.alphaTextureMap.GetData().c_str()))

			<< endl << material.ambientTextureMap.GetWidth()
			<< space << material.ambientTextureMap.GetHeight()
			<< space << material.ambientTextureMap.GetNrChannels()
			<< space << base64_encode((const unsigned char*)material.ambientTextureMap.GetData().c_str(), strlen(material.ambientTextureMap.GetData().c_str()))

			<< endl << material.diffuseTextureMap.GetWidth()
			<< space << material.diffuseTextureMap.GetHeight()
			<< space << material.diffuseTextureMap.GetNrChannels()
			<< space << base64_encode((const unsigned char*)material.diffuseTextureMap.GetData().c_str(), strlen(material.diffuseTextureMap.GetData().c_str()))
			<< endl;
	}

	result << endl;

	vector<Object> objects = model.GetObjects();
	for (size_t i = 0; i < objects.size(); i++)
	{
		result << objects[i].GetName() << endl;

		vector<Mesh> meshes = objects[i].GetMeshes();
		for (size_t ii = 0; ii < meshes.size(); ii++)
		{
			Mesh& mesh = meshes[ii];
			result << mesh.GetMaterial().name;
			
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
			result << endl;
		}
		result << endl;
	}

	string data = result.str();

	stringstream stringStream;
	stringStream << time(nullptr);
	string saveFileLocation = "C:/Exports/" + stringStream.str() + ".basic";

	fileUtils.SaveFile(data, saveFileLocation);*/
}

void BasicModelLoader::GetModel(Model& model, std::string fileLocation, GLuint& program)
{
	/*string fileData = fileUtils.ReadFile(fileLocation);

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
		material.ambientColour.r = stof(GetNextWord(remaining));
		material.ambientColour.g = stof(GetNextWord(remaining));
		material.ambientColour.b = stof(GetNextWord(remaining));
		material.diffuseColour.r = stof(GetNextWord(remaining));
		material.diffuseColour.g = stof(GetNextWord(remaining));
		material.diffuseColour.b = stof(GetNextWord(remaining));
		material.specularColour.r = stof(GetNextWord(remaining));
		material.specularColour.g = stof(GetNextWord(remaining));
		material.specularColour.b = stof(GetNextWord(remaining));
		material.specularColourWeight = stof(GetNextWord(remaining));
		material.dissolve = stof(GetNextWord(remaining));
		material.illuminationModel = stof(GetNextLine(remaining));

		material.alphaTextureMap.SetWidth(stoi(GetNextWord(remaining)));
		material.alphaTextureMap.SetHeight(stoi(GetNextWord(remaining)));
		material.alphaTextureMap.SetNrChannels(stoi(GetNextWord(remaining)));
		string alphaTexture = base64_decode(GetNextLine(remaining));
		//const unsigned char* c_alphaTexture = (const unsigned char*)alphaTexture.c_str();
		material.alphaTextureMap.SetData(alphaTexture);

		material.ambientTextureMap.SetWidth(stoi(GetNextWord(remaining)));
		material.ambientTextureMap.SetHeight(stoi(GetNextWord(remaining)));
		material.ambientTextureMap.SetNrChannels(stoi(GetNextWord(remaining)));
		string ambientData = base64_decode(GetNextLine(remaining));
		//const unsigned char* c_ambientData = (const unsigned char*)ambientData.c_str();
		material.ambientTextureMap.SetData(ambientData);

		material.diffuseTextureMap.SetWidth(stoi(GetNextWord(remaining)));
		material.diffuseTextureMap.SetHeight(stoi(GetNextWord(remaining)));
		material.diffuseTextureMap.SetNrChannels(stoi(GetNextWord(remaining)));
		string diffuseData = base64_decode(GetNextLine(remaining));
		//const unsigned char* c_diffuseData = (const unsigned char*)diffuseData.c_str();
		material.diffuseTextureMap.SetData(diffuseData);

		model.AddMaterial(material);
		word = remaining[0] == '\n' ? empty : GetNextWord(remaining);
	}

	word = GetNextLine(remaining);

	Object object = Object(program);
	string name = word;
	object.SetName(name);
	char* line = GetNextLine(remaining);
	while (line != NULL)
	{
		Mesh mesh = Mesh(program);
		string materialName = GetNextWord(line);
		mesh.SetMaterial(model.GetMaterial(materialName));

		while (strcmp(line, "") != 0)
		{
			Vertex vertex = Vertex();
			
			vertex.SetPosition(
				stof(GetNextWord(line)),
				stof(GetNextWord(line)),
				stof(GetNextWord(line)));

			vertex.SetNormal(
				stof(GetNextWord(line)),
				stof(GetNextWord(line)),
				stof(GetNextWord(line)));

			vertex.SetColour(
				stof(GetNextWord(line)),
				stof(GetNextWord(line)),
				stof(GetNextWord(line)),
				stof(GetNextWord(line)));

			vertex.SetTexture(
				stof(GetNextWord(line)),
				stof(GetNextWord(line)));

			vertices.push_back(vertex);
			indices.push_back(counter);
			counter++;
		}

		mesh.SetIndicies(indices);
		mesh.SetVertices(vertices);

		object.AddMesh(mesh);

		line = GetNextLine(remaining);

		if (true)
		{
			model.AddObject(object);
		}
	}*/
}

char* BasicModelLoader::GetNextWord(char*& remaining)
{
	return strtok_s(remaining, " ", &remaining);
}

char* BasicModelLoader::GetNextLine(char*& remaining)
{
	return strtok_s(remaining, "\n", &remaining);
}