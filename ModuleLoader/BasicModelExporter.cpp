#include "BasicModelExporter.h"

#include "Vertex.h"

#include <sstream>
#include <iostream>
#include <ctime>

using namespace std;

BasicModelExporter::BasicModelExporter(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

void BasicModelExporter::Export(Model& model)
{
	char space = ' ';
	ostringstream result;

	vector<Object> objects = model.GetObjects();
	for (size_t i = 0; i < objects.size(); i++)
	{
		vector<Mesh> meshes = objects[i].GetMeshes();
		for (size_t ii = 0; ii < meshes.size(); ii++)
		{
			vector<Vertex> vertices = meshes[ii].GetVertices();
			vector<GLuint> indices = meshes[ii].GetIndicies();

			for (size_t iii = 0; iii < indices.size(); iii++)
			{
				Vertex vertex = vertices[indices[iii]];

				result << vertex.position.x;
				result << space;
				result << vertex.position.y;
				result << space;
				result << vertex.position.z;
				result << space;

				result << vertex.normal.x;
				result << space;
				result << vertex.normal.y;
				result << space;
				result << vertex.normal.z;
				result << space;

				result << vertex.colour.r;
				result << space;
				result << vertex.colour.g;
				result << space;
				result << vertex.colour.b;
				result << space;
				result << vertex.colour.a;
				result << space;

				result << vertex.texture.x;
				result << space;
				result << vertex.texture.y;
				result << space;
			}
		}
	}

	string data = result.str();

	stringstream stringStream;
	stringStream << time(nullptr);
	string saveFileLocation = "C:/Exports/" + stringStream.str() + ".basic";

	fileUtils.SaveFile(data, saveFileLocation);
}