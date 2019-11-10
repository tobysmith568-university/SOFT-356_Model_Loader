#include "ObjModelLoader.h"
#include "Vertex.h"

using namespace std;

ObjModelLoader::ObjModelLoader(FileUtils& _fileUtils, MtlLoader& _mtlLoader)
	: fileUtils(_fileUtils), mtlLoader(_mtlLoader)
{
}

void ObjModelLoader::GetModel(Model& model, std::string fileLocation)
{
	Object* object = nullptr;
	Mesh* mesh = nullptr;

	vector<GLfloat> vertexValues = vector<GLfloat>();
	vector<GLfloat> textureCoordValues = vector<GLfloat>();
	vector<GLfloat> normalValues = vector<GLfloat>();
	vector<Face> faceValues = vector<Face>();

	string folder = fileUtils.GetFolder(fileLocation);
	vector<string> fileLines = fileUtils.ReadFileAsLines(fileLocation);

	for (size_t i = 0; i < fileLines.size(); i++)
	{
		char* c_line = (char*)fileLines[i].c_str();

		if (strncmp(c_line, "mtllib ", 7) == 0)
		{
			ReadMaterials(model, fileLines[i], folder);
		}
		else if (strncmp(c_line, "o ", 2) == 0)
		{
			if (object != nullptr)
			{
				model.AddObject(*object);
			}

			string name = GetSingleString(fileLines[i]);

			object = &Object();
			object->SetName(name);
		}
		else if (object == nullptr)
		{
			continue;
		}
		else if (strncmp(c_line, "usemtl ", 2) == 0)
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
			mesh = &Mesh();
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
			ReadFace(faceValues, fileLines[i]);
		}
	}

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

	if (object != nullptr)
	{
		model.AddObject(*object);
	}
}

char* ObjModelLoader::GetSingleString(std::string& line)
{
	char* value;
	char* remaining;
	value = strtok_s((char*)line.c_str(), " ", &remaining);
	value = strtok_s(remaining, " ", &remaining);

	return value;
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

void ObjModelLoader::ReadMaterials(Model& model, string& line, string& folder)
{
	char* materialFileLocation;
	char* remaining;
	materialFileLocation = strtok_s((char*)line.c_str(), " ", &remaining);
	materialFileLocation = strtok_s(remaining, " ", &remaining);

	string materialLocation = folder + materialFileLocation;

	mtlLoader.LoadMaterials(model, materialLocation);
}

void ObjModelLoader::SetVertices(Mesh& mesh,
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

	mesh.SetVertices(vertices);
}

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

std::string ObjModelLoader::GetTextureName(std::string& fileLocation)
{
	return "media/Texture.png";
}