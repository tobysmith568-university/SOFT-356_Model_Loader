#include "BasicModelLoader.h"

#include "Vertex.h"
#include "Base64.h"
#include "stb_image.h"

#include <sstream>
#include <iostream>

using namespace std;

BasicModelLoader::BasicModelLoader(FileUtils& _fileUtils, ConsoleUtil& _consoleUtil)
	: fileUtils(_fileUtils), consoleUtil(_consoleUtil)
{
}

// Exports a model to a .basic file on disk
void BasicModelLoader::Export(Model& model)
{
	consoleUtil.ClearConsole();
	string saveFileLocation = consoleUtil.GetInput("Enter a file name for the exported model");

	ostringstream result;

	vector<Material> materials = model.GetMaterials();

	Material material;
	for (size_t i = 0; i < materials.size(); i++)// For every material in the model
	{
		if (i != 0)// Assuming it's not the first one, add a new line
		{
			result << endl;
		}

		material = materials[i];

		string alphaPath = material.alphaTextureMap.GetPath();// Get the image location without folders or get "no.png"
		alphaPath = alphaPath.size() == 0 ? noPNG : fileUtils.GetFileName(alphaPath);

		string ambientPath = material.ambientTextureMap.GetPath();
		ambientPath = ambientPath.size() == 0 ? noPNG : fileUtils.GetFileName(ambientPath);

		string diffusePath = material.diffuseTextureMap.GetPath();
		diffusePath = diffusePath.size() == 0 ? noPNG : fileUtils.GetFileName(diffusePath);

		result << material.name// Print every value from the material to the output stream
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
			<< endl << alphaPath
			<< endl << ambientPath
			<< endl << diffusePath;
	}

	vector<Object> objects = model.GetObjects();
	for (size_t i = 0; i < objects.size(); i++)// For every object in the model
	{
		result << endl << endl << objects[i].GetName();

		vector<Mesh> meshes = objects[i].GetMeshes();
		for (size_t ii = 0; ii < meshes.size(); ii++)// For every mesh in the model
		{
			Mesh& mesh = meshes[ii];
			result << endl << mesh.GetMaterial().name;
			
			vector<Vertex> vertices = mesh.GetVertices();
			vector<GLuint> indices = mesh.GetIndicies();

			for (size_t iii = 0; iii < indices.size(); iii++)// For every index
			{
				Vertex vertex = vertices[indices[iii]];

				result << space << vertex.position.x;// Print out every value from the related vertex
				result << space << vertex.position.y;
				result << space << vertex.position.z;
				result << space << vertex.normal.x;
				result << space << vertex.normal.y;
				result << space << vertex.normal.z;
				result << space << vertex.texture.x;
				result << space << vertex.texture.y;
			}
		}
	}

	string data = result.str();

	fileUtils.SaveFile(data, saveFileLocation);// Save the file to disk
	consoleUtil.ClearConsole();
}

// Reads in a .basic file from disk
void BasicModelLoader::GetModel(Model& model, std::string fileLocation, GLuint& program)
{
	string folder = fileUtils.GetFolder(fileLocation);
	string fileData = fileUtils.ReadFile(fileLocation);// Read in the file

	vector<Vertex> vertices = vector<Vertex>();
	vector<GLuint> indices = vector<GLuint>();

	char* word = empty;
	char* remaining = (char*)fileData.c_str();

	GLuint counter = 0;
	word = GetNextWord(remaining);

	while (word != empty)// While the data is not empty - this means while there are more materials
	{
		Material material = Material();
		material.name = word;
		material.ambientColour.r = GetNextWordAsFloat(remaining);// Load in most material data from a single line
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

		string textureLine = GetNextLine(remaining);// Load in texture paths from their own lines
		GetTexture(material.alphaTextureMap, textureLine, folder);

		textureLine = GetNextLine(remaining);
		GetTexture(material.ambientTextureMap, textureLine, folder);

		textureLine = GetNextLine(remaining);
		GetTexture(material.diffuseTextureMap, textureLine, folder);

		model.AddMaterial(material);
		word = remaining[0] == newLine ? empty : GetNextWord(remaining);
	}

	// Now all the materials have been read in, just the meshes remain

	word = GetNextLine(remaining);

	char* line = GetNextLine(remaining);
	Object* object = nullptr;
	Mesh* mesh = nullptr;

	object = new Object(program);
	string name = word;
	object->SetName(name);

	while (line != NULL)// While there are meshes still in the data
	{
		mesh = new Mesh(program);
		vertices = vector<Vertex>();
		indices = vector<GLuint>();
		counter = 0;
		string materialName = GetNextWord(line);// Read in the material from it's name
		Material material = model.GetMaterial(materialName);
		mesh->SetMaterial(material);

		while (strcmp(line, empty) != 0)// While there are more 'words' on the line
		{
			Vertex vertex = Vertex();

			GLfloat posX = GetNextWordAsFloat(line);// Read in a position
			GLfloat posY = GetNextWordAsFloat(line);
			GLfloat posZ = GetNextWordAsFloat(line);

			vertex.SetPosition(posX, posY, posZ);

			GLfloat normX = GetNextWordAsFloat(line);// Read in a normal
			GLfloat normY = GetNextWordAsFloat(line);
			GLfloat normZ = GetNextWordAsFloat(line);

			vertex.SetNormal(normX, normY, normZ);

			vertex.SetColour(material.diffuseColour.r,// Take the colour from the current material
				material.diffuseColour.g,
				material.diffuseColour.b,
				material.dissolve);

			GLfloat texX = GetNextWordAsFloat(line);// Read in a texture coord
			GLfloat texY = GetNextWordAsFloat(line);

			vertex.SetTexture(texX, texY);

			vertices.push_back(vertex);
			indices.push_back(counter);// Create in index
			counter++;
		}

		mesh->SetIndicies(indices);// Add the vertices and indices
		mesh->SetVertices(vertices);

		object->AddMesh(*mesh);// Add the mesh to the current object
		
		if (remaining[0] == newLine)// If an empty line has been reached
		{
			model.AddObject(*object);// Add the object and create a new one
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

// Loads in a texture
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