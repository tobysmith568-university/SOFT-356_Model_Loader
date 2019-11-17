#include "DaeModelLoader.h"
#include <regex>

using namespace std;

DaeModelLoader::DaeModelLoader(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

void DaeModelLoader::GetModel(Model& model, std::string fileLocation, GLuint& program)
{
	string folder = fileUtils.GetFolder(fileLocation);
	string fileData = fileUtils.ReadFile(fileLocation);// Reads the file into memory

	map<string, vector<GLfloat>> sources = map<string, vector<GLfloat>>();
	map<string, vector<Input>> vertices = map<string, vector<Input>>();
	vector<Triangle> triangles = vector<Triangle>();

	ParseSources(sources, fileData);
	ParseVertices(vertices, fileData);
	ParseTriangles(triangles, fileData);
}

void DaeModelLoader::ParseSources(std::map<std::string, std::vector<GLfloat>>& sources, std::string fileData)
{
	const regex sourceRegex("<source.+?id=\"([A-Za-z0-9-_]+?)\">[\\s\\S]*?<float_array.*?>([\\d -.e]+)?<\\/float_array>");
	smatch sm;

	while (regex_search(fileData, sm, sourceRegex))// While regex matches are found in the file
	{
		if (sm.size() != 3)
		{
			continue;
		}

		if (!sm[0].matched || !sm[1].matched || !sm[2].matched)
		{
			continue;
		}

		string values = sm[2];

		sources[sm[1]] = vector<GLfloat>();
		ReadSpaceSepFloats(sources[sm[1]], values);
		fileData = sm.suffix();
	}
}

void DaeModelLoader::ParseVertices(std::map<std::string, std::vector<Input>>& vertices, std::string fileData)
{
	const regex sourceRegex("<vertices[\\s\\S]*?id=\"(.*?)\"[\\s\\S]*?>([\\s\\S]+)<\\/vertices>");
	smatch sm;

	while (regex_search(fileData, sm, sourceRegex))// While regex matches are found in the file
	{
		if (sm.size() != 3)
		{
			continue;
		}

		if (!sm[0].matched || !sm[1].matched || !sm[2].matched)
		{
			continue;
		}

		vector<Input> inputs = vector <Input>();
		ReadInputs(inputs, sm[2]);

		vertices[sm[1]] = inputs;
		fileData = sm.suffix();
	}
}

void DaeModelLoader::ParseTriangles(std::vector<Triangle>& triangles, std::string fileData)
{
	const regex sourceRegex("<triangles material=\"([A-Za-z0-9-_]+)\"[\\s\\S]*?>([\\s\\S]*?)<\\/triangles>");
	smatch sm;

	while (regex_search(fileData, sm, sourceRegex))// While regex matches are found in the file
	{
		if (sm.size() != 3)
		{
			continue;
		}

		if (!sm[0].matched || !sm[1].matched || !sm[2].matched)
		{
			continue;
		}

		string material = sm[1];

		vector<Input> inputs = vector <Input>();
		ReadInputs(inputs, sm[2]);

		vector<GLfloat> indices = vector<GLfloat>();
		ReadIndices(indices, sm[2]);

		fileData = sm.suffix();
	}
}

void DaeModelLoader::ReadInputs(std::vector<Input>& inputs, std::string inputData)
{
	const regex sourceRegex("<input(?: *([A-z]+?)=\"(.*?)\")?(?: *([A-z]+?)=\"(.*?)\")?(?: *([A-z]+?)=\"(.*?)\")?(?: *([A-z]+?)=\"(.*?)\")?.*?\/>");
	smatch sm;

	while (regex_search(inputData, sm, sourceRegex))// While regex matches are found in the file
	{
		if (sm.size() != 9)
		{
			continue;
		}

		if (!sm[0].matched)
		{
			continue;
		}

		Input input = Input();
		ReadInput(input, sm);

		inputs.push_back(input);

		inputData = sm.suffix();
	}
}

void DaeModelLoader::ReadInput(Input& input, std::smatch& match)
{
	for (size_t i = 1; i < match.size(); i += 2)
	{
		if (!match[i].matched || !match[i + 1].matched)
		{
			continue;
		}

		if (match[i] == "semantic")
		{
			input.SetSemantic(match[i + 1]);
		}
		else if (match[i] == "source")
		{
			input.SetSource(match[i + 1]);
		}
		else if (match[i] == "offset")
		{
			input.SetOffset(match[i + 1]);
		}
		else if (match[i] == "set")
		{
			input.SetSet(match[i + 1]);
		}
	}
}

void DaeModelLoader::ReadIndices(std::vector<GLfloat> indices, std::string inputData)
{
	const regex sourceRegex("<p>([0-9 ]+)<\/p>");
	smatch sm;

	while (regex_search(inputData, sm, sourceRegex))// While regex matches are found in the file
	{
		if (sm.size() != 2)
		{
			continue;
		}

		if (!sm[0].matched || !sm[1].matched)
		{
			continue;
		}

		string data = sm[1];
		ReadSpaceSepFloats(indices, data);

		inputData = sm.suffix();
	}
}

void DaeModelLoader::ReadSpaceSepFloats(std::vector<GLfloat>& floats, std::string& line)
{
	char* word;
	char* remaining;
	word = strtok_s((char*)line.c_str(), " ", &remaining);
	while (word != NULL)
	{
		floats.push_back(stof(word));
		word = strtok_s(remaining, " ", &remaining);
	}
}