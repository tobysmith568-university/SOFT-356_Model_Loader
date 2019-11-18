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

	map<string, Source> sources = map<string, Source>();
	string vertexID, vertexSource, material;
	vector<Input> inputs = vector<Input>();
	vector<GLfloat> faceData = vector<GLfloat>();
	vector<Vertex> vertices = vector<Vertex>();

	ParseSources(sources, fileData);
	ParseVertexInput(vertexID, vertexSource, fileData);
	ParseTriangleInputs(inputs, material, fileData);

	for (size_t i = 0; i < inputs.size(); i++)
	{
		if (inputs[i].GetSource() == vertexID)
		{
			inputs[i].SetSource(vertexSource);
		}
	}

	PairInputsAndSources(inputs, sources);

	ParseFaceData(faceData, fileData);

	CreateVertices(vertices, inputs, faceData);
}

void DaeModelLoader::ParseSources(std::map<std::string, Source>& sources, std::string fileData)
{
	const regex sourceRegex("<source [\\s\\S]*?id=\"([A-Za-z0-9-_]+?)\">[\\s\\S]*?<float_array[\\s\\S]*?>([\\d -.e]+)?<\\/float_array>[\\s\\S]*?<technique_common>[\\s\\S]*?<accessor [\\s\\S]*?stride=\"(\\d+)\">");
	smatch sm;

	while (regex_search(fileData, sm, sourceRegex))// While regex matches are found in the file
	{
		if (sm.size() != 4)
		{
			continue;
		}

		if (!sm[0].matched || !sm[1].matched || !sm[2].matched || !sm[3].matched)
		{
			continue;
		}

		string values = sm[2];
		string stride = sm[3];

		vector<GLfloat> floats;
		ReadSpaceSepFloats(floats, values);

		Source newSource = Source();
		newSource.SetData(floats);
		newSource.SetStride(stoi(stride));

		sources[sm[1]] = newSource;

		fileData = sm.suffix();
	}
}

void DaeModelLoader::ParseVertexInput(std::string& vertexID, std::string& vertexSource, std::string fileData)
{
	const regex sourceRegex("<vertices[\\s\\S]*?id=\"(.*?)\"[\\s\\S]*?>[\\s\\S]*?<input [\\s\\S]*?source=\"([\\s\\S]+?)\"[\\s\\S]+?<\\/vertices>");
	smatch sm;

	if (regex_search(fileData, sm, sourceRegex))// If a regex match is found in the file
	{
		if (sm.size() != 3)
		{
			return;
		}

		if (!sm[0].matched || !sm[1].matched || !sm[2].matched)
		{
			return;
		}

		vertexID = sm[1];
		vertexSource = sm[2];
	}
}

void DaeModelLoader::ParseTriangleInputs(std::vector<Input>& inputs, std::string& material, std::string fileData)
{
	const regex sourceRegex("<triangles material=\"([A-Za-z0-9-_]+)\"[\\s\\S]*?>([\\s\\S]*?)<\\/triangles>");
	smatch sm;

	if (regex_search(fileData, sm, sourceRegex))// If a regex match is found in the file
	{
		if (sm.size() != 3)
		{
			return;
		}

		if (!sm[0].matched || !sm[1].matched || !sm[2].matched)
		{
			return;
		}

		material = sm[1];

		ReadInputs(inputs, sm[2]);

		fileData = sm.suffix();
	}
}

void DaeModelLoader::ParseFaceData(vector<GLfloat>& faceData, std::string fileData)
{
	const regex sourceRegex("<triangles [\\s\\S]*?>[\\s\\S]+?<p>([\\d ]+?)<\\/p>[\\s\\S]*?<\\/triangles>");
	smatch sm;

	if (regex_search(fileData, sm, sourceRegex))// If a regex match is found in the file
	{
		if (sm.size() != 2)
		{
			return;
		}

		if (!sm[0].matched || !sm[1].matched)
		{
			return;
		}

		string data = sm[1];
		ReadSpaceSepFloats(faceData, data);
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

void DaeModelLoader::PairInputsAndSources(std::vector<Input>& inputs, std::map<std::string, Source>& sources)
{
	for (size_t i = 0; i < inputs.size(); i++)
	{
		string key = inputs[i].GetSource();

		if (key.length() > 0 && key[0] == '#')
		{
			key = key.substr(1, key.size());
		}

		if (sources.count(key) != 0)
		{
			inputs[i].SetData(sources[key].GetData());
			inputs[i].SetDataStride(sources[key].GetStride());
		}
	}
}

void DaeModelLoader::CreateVertices(std::vector<Vertex>& vertices, std::vector<Input>& inputs, std::vector<GLfloat>& indices)
{

}
