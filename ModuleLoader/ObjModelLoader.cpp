#include "ObjModelLoader.h"
#include "Vertex.h"
#include "InvalidModelFileException.h"

using namespace std;

ObjModelLoader::ObjModelLoader(FileUtils& _fileUtils, ConsoleUtil& _consoleUtil, MtlLoader& _mtlLoader)
	: fileUtils(_fileUtils), consoleUtil(_consoleUtil), mtlLoader(_mtlLoader)
{
}

void ObjModelLoader::GetModel(Model& model, std::string fileLocation, GLuint& program)
{
	Object* object = nullptr;
	Mesh* mesh = nullptr;

	vector<GLfloat> vertexValues = vector<GLfloat>();
	vector<GLfloat> textureCoordValues = vector<GLfloat>();
	vector<GLfloat> normalValues = vector<GLfloat>();
	vector<Face> faceValues = vector<Face>();

	string folder = fileUtils.GetFolder(fileLocation);
	vector<string> fileLines = fileUtils.ReadFileAsLines(fileLocation);// Reads the file into memory

	for (size_t i = 0; i < fileLines.size(); i++)// Runs code on each line in the file depending on what it begins with
	{
		char* c_line = (char*)fileLines[i].c_str();

		if (strncmp(c_line, "mtllib ", 7) == 0)// Loads in a material file
		{
			ReadMaterials(model, fileLines[i], folder);
		}
		else if (strncmp(c_line, "o ", 2) == 0)// This line indicates that a new object is needed
		{
			if (object != nullptr)
			{
				if (object->GetMeshes().size() == 0)
				{
					throw InvalidModelFileException(fileLocation.c_str(), ("The object [" + object->GetName() + "] has no material lines").c_str());
				}

				model.AddObject(*object);
			}

			string name = GetSingleString(fileLines[i]);

			object = &Object(program);
			object->SetName(name);
		}
		else if (object == nullptr)// If there is no object line in the file so far, then the other options are irrelevant
		{
			continue;
		}
		else if (strncmp(c_line, "usemtl ", 2) == 0)// This line indicates that a new mesh is needed
		{
			if (mesh != nullptr)
			{
				SetVertices(*mesh,
					vertexValues,
					textureCoordValues,
					normalValues,
					faceValues);
				SetIndices(*mesh, faceValues);

				object->AddMesh(*mesh);
			}

			faceValues = vector<Face>();
			mesh = &Mesh(program);
			string materialName = GetSingleString(fileLines[i]);
			mesh->SetMaterial(model.GetMaterial(materialName));
		}
		else if (strncmp(c_line, "v ", 2) == 0)
		{
			ReadSpaceSepFloats(vertexValues, fileLines[i]);
		}
		else if (strncmp(c_line, "vt ", 3) == 0)
		{
			ReadSpaceSepFloats(textureCoordValues, fileLines[i]);
		}
		else if (strncmp(c_line, "vn ", 3) == 0)
		{
			ReadSpaceSepFloats(normalValues, fileLines[i]);
		}
		else if (strncmp(c_line, "f ", 2) == 0)
		{
			ReadFace(faceValues, fileLines[i], fileLocation);
		}
	}

	if (mesh != nullptr)// The 'new mesh' code above adds meshes to the current object, but at the end of the file, the final one also needs adding
	{
		SetVertices(*mesh,
			vertexValues,
			textureCoordValues,
			normalValues,
			faceValues);
		SetIndices(*mesh, faceValues);

		object->AddMesh(*mesh);
	}

	if (object != nullptr)// The 'new  object' code above adds meshes to the current model, but at the end of the file, the final one also needs adding
	{
		if (object->GetMeshes().size() == 0)
		{
			throw InvalidModelFileException(fileLocation.c_str(), ("The object [" + object->GetName() + "] has no material lines").c_str());
		}

		model.AddObject(*object);
	}

	if (model.GetObjects().size() == 0)// Catches a file with no objects
	{
		throw InvalidModelFileException(fileLocation.c_str(), "The given file has no object lines");
	}
}

// Returns a line from the file with the prefix removed
char* ObjModelLoader::GetSingleString(std::string& line)
{
	char* value;
	char* remaining;
	value = strtok_s((char*)line.c_str(), " ", &remaining);
	value = strtok_s(remaining, " ", &remaining);

	return value;
}

// Reads in floats from a line in the file which are space separated
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

// Reads in all x/x/x style groups from a line in the file into the given faces vector
void ObjModelLoader::ReadFace(std::vector<Face>& faces, std::string& line, std::string& fileName)
{
	GLuint count = 0;
	try
	{
		Face face = Face();

		char* word;
		char* remaining;
		word = strtok_s((char*)line.c_str(), " ", &remaining);
		word = strtok_s(remaining, " ", &remaining);
		while (word != NULL && count < 4)// For each group of numbers upto 4
		{
			ReadIndex(face, word);
			word = strtok_s(remaining, " ", &remaining);
			count++;
		}

		if (word != NULL)// If there is more than 4 or any extra data
		{
			string data = word + (string)remaining;
			consoleUtil.Print("\nFound additional data which cannot be rendered:\n" + data);
		}

		faces.push_back(face);
	}
	catch (...)
	{
		//The catch code is the code below.
		//It needs to be run either way in order to also catch too little data as well as too much
	}

	while (count % 3 != 0 && count % 4 != 0)// The data only works with multiples of either 3 or 4 indices
	{
		faces[faces.size() - 1].GetIndices().pop_back();// Removes any extra indices until there is a multiple of 3 or 4
		consoleUtil.Print("\nInvalid data!\nThe resulting model may be missing some faces");
		count--;
	}

	if (faces[faces.size() - 1].GetIndices().size() == 0)// Catches empty faces
	{
		throw InvalidModelFileException(fileName, "One or more faces contains no valid data");
	}
}

// Splits up x/x/x groups of data in an index on the given face
void ObjModelLoader::ReadIndex(Face& face, char* index)
{
	GLuint value = 0;

	Index newIndex = Index();

	char* word;
	char* remaining;
	word = strtok_s(index, "/", &remaining);
	while (word != NULL)// For each number in the x/y/z
	{
		if (value == 0)// X in x/y/z
		{
			newIndex.vertexIndex = stoi(word);
		}
		else if (value == 1)// Y in x/y/z
		{
			newIndex.textureIndex = stoi(word);
		}
		else if (value == 2)// Z in x/y/z
		{
			newIndex.normalIndex = stoi(word);
		}

		value++;
		word = strtok_s(remaining, "/", &remaining);
	}

	face.AddIndex(newIndex);
}

// Reads in a material file
void ObjModelLoader::ReadMaterials(Model& model, string& line, string& folder)
{
	char* materialFileLocation;
	char* remaining;
	materialFileLocation = strtok_s((char*)line.c_str(), " ", &remaining);
	materialFileLocation = strtok_s(remaining, " ", &remaining);

	string materialLocation = folder + materialFileLocation;

	mtlLoader.LoadMaterials(model, materialLocation);
}

// Generates the vertex data on a mesh using the data read from file
void ObjModelLoader::SetVertices(Mesh& mesh,
	vector<GLfloat>& vertexValues,
	vector<GLfloat>& textureCoordValues,
	vector<GLfloat>& normalValues,
	vector<Face>& faceValues)
{
	vector<Vertex> vertices = vector<Vertex>();

	for (size_t i = 0; i < faceValues.size(); i++)// For every face
	{
		vector<Index> indices = faceValues[i].GetIndices();

		for (size_t ii = 0; ii < indices.size(); ii++)// For every index within the face
		{
			Vertex vertex = Vertex();

			GLuint vertexValue = ((indices[ii].vertexIndex - 1) * 3);// Get the correct index data
			GLuint textureValue = ((indices[ii].textureIndex - 1) * 2);// 2 not 3 because a texture coord is only X and Y
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

			vertex.SetColour(
				mesh.GetMaterial().diffuseColour.r,
				mesh.GetMaterial().diffuseColour.g,
				mesh.GetMaterial().diffuseColour.b,
				mesh.GetMaterial().dissolve);

			vertices.push_back(vertex);
		}
	}

	mesh.SetVertices(vertices);
}

// Generates the indices for a mesh with their given offsets in the vertex data
void ObjModelLoader::SetIndices(Mesh& mesh, vector<Face>& faces)
{
	vector<GLuint> indices = vector<GLuint>();

	GLuint offset = 0;
	for (size_t i = 0; i < faces.size(); i++)
	{
		offset = faces[i].GetOffset(indices, offset);
	}

	mesh.SetIndicies(indices);
}