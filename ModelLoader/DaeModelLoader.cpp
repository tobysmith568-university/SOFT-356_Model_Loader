#include "DaeModelLoader.h"
#include <regex>
#include "stb_image.h"

using namespace std;

DaeModelLoader::DaeModelLoader(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

void DaeModelLoader::GetModel(Model& model, std::string fileLocation, GLuint& program)
{
	string folder = fileUtils.GetFolder(fileLocation);
	string fileData = fileUtils.ReadFile(fileLocation);// Reads the file into memory

	map<string, Source> sources = map<string, Source>();// Create empty data to be populated
	string vertexID, vertexSource, materialName;
	vector<Input> inputs = vector<Input>();
	vector<GLfloat> faceData = vector<GLfloat>();
	vector<Vertex> vertices = vector<Vertex>();
	Material material = Material();

	ParseSources(sources, fileData);// Parse the file for the data
	ParseVertexInput(vertexID, vertexSource, fileData);
	ParseTriangleInputs(inputs, materialName, fileData);

	for (size_t i = 0; i < inputs.size(); i++)// Replaces the VERTEX source with the POSITION source
	{
		if (inputs[i].GetSource() == vertexID)
		{
			inputs[i].SetSource(vertexSource);
		}
	}

	PairInputsAndSources(inputs, sources);

	ParseFaceData(faceData, fileData);
	ParseMaterial(material, fileData, folder);

	OrderInputsByOffset(inputs);// Sort the data and create the model
	CreateVertices(vertices, inputs, faceData);
	BuildModel(model, material, vertices, program);
}

// Reads in all the source tags from the file
void DaeModelLoader::ParseSources(std::map<std::string, Source>& sources, std::string fileData)
{
	const regex sourceRegex("<source [\\s\\S]*?id=\"([A-Za-z0-9-_]+?)\"[\\s\\S]*?>[\\s\\S]*?<float_array[\\s\\S]*?>([\\d -.e]+)?<\\/float_array>[\\s\\S]*?<technique_common>[\\s\\S]*?<accessor [\\s\\S]*?stride=\"(\\d+)\">");
	smatch sm;

	while (regex_search(fileData, sm, sourceRegex))// While regex matches are found in the file
	{
		if (sm.size() != 4)// Ensure there are 4 matches
		{
			continue;
		}

		if (!sm[0].matched || !sm[1].matched || !sm[2].matched || !sm[3].matched)// Ensure all 4 matches found something
		{
			continue;
		}

		string values = sm[2];
		string stride = sm[3];

		vector<GLfloat> floats;
		ReadSpaceSepFloats(floats, values);

		Source newSource = Source();// Create a new Source object and set the data and stride
		newSource.SetData(floats);
		newSource.SetStride(stoi(stride));

		sources[sm[1]] = newSource;// Add the new Source paired up with it's ID

		fileData = sm.suffix();// Change the source data to start where the previous match finished
	}
}

// Reads in a vertex tag from the file
void DaeModelLoader::ParseVertexInput(std::string& vertexID, std::string& vertexSource, std::string fileData)
{
	const regex sourceRegex("<vertices[\\s\\S]*?id=\"(.*?)\"[\\s\\S]*?>[\\s\\S]*?<input [\\s\\S]*?source=\"([\\s\\S]+?)\"[\\s\\S]+?<\\/vertices>");
	smatch sm;

	if (regex_search(fileData, sm, sourceRegex))// If a regex match is found in the file
	{
		if (sm.size() != 3)// Ensure there are 3 matches
		{
			return;
		}

		if (!sm[0].matched || !sm[1].matched || !sm[2].matched)// Ensure all 3 matches found something
		{
			return;
		}

		vertexID = sm[1];
		vertexSource = sm[2];
	}
}

// Reads in input tags from within a triangle tag the file
void DaeModelLoader::ParseTriangleInputs(std::vector<Input>& inputs, std::string& material, std::string fileData)
{
	const regex sourceRegex("<triangles (?:material=\"([A-Za-z0-9-_]+)\")?[\\s\\S]*?>([\\s\\S]*?)<\\/triangles>");
	smatch sm;

	if (regex_search(fileData, sm, sourceRegex))// If a regex match is found in the file
	{
		if (sm.size() != 3)// Ensure there are 3 matches
		{
			return;
		}

		if (!sm[0].matched || !sm[2].matched)// Ensure match 0 and 2 found something
		{
			return;
		}

		if (sm[1].matched)// If match 1 found something, set it as a material
		{
			material = sm[1];
		}

		ReadInputs(inputs, sm[2]);

		fileData = sm.suffix();// Change the source data to start where the previous match finished
	}
}

// Reads in a p tag from a triangle tag from the file
void DaeModelLoader::ParseFaceData(vector<GLfloat>& faceData, std::string fileData)
{
	const regex sourceRegex("<triangles [\\s\\S]*?>[\\s\\S]+?<p>([\\d ]+?)<\\/p>[\\s\\S]*?<\\/triangles>");
	smatch sm;

	if (regex_search(fileData, sm, sourceRegex))// If a regex match is found in the file
	{
		if (sm.size() != 2)// Ensure there are 2 matches
		{
			return;
		}

		if (!sm[0].matched || !sm[1].matched)// Ensure both matches found something
		{
			return;
		}

		string data = sm[1];
		ReadSpaceSepFloats(faceData, data);
	}
}

// Reads in a texture name from the file and wraps it in a material
void DaeModelLoader::ParseMaterial(Material& material, string fileData, string folder)
{
	const regex sourceRegex("<library_images>[\\s\\S]*?<image [\\s\\S]+?>[\\s\\S]+?<init_from>([A-z.]+?)<\\/init_from>[\\s\\S]*?<\\/image>[\\s\\S]*?<\\/library_images>");
	smatch sm;

	if (regex_search(fileData, sm, sourceRegex))// If a regex match is found in the file
	{
		if (sm.size() != 2)// Ensure there are 2 matches
		{
			return;
		}

		if (!sm[0].matched || !sm[1].matched)// Ensure both matches found something
		{
			return;
		}

		string fileLocation = folder;
		fileLocation += sm[1];// Create the full file path

		if (!fileUtils.DoesFileExist(fileLocation))
		{
			return;
		}

		Texture texture = Texture();// Load in a texture using that file path and set it to the diffuse texture
		GetTexture(texture, sm[1], fileLocation);
		material.diffuseTextureMap = texture;
	}
}

// Reads in any input tags from the given data
void DaeModelLoader::ReadInputs(std::vector<Input>& inputs, std::string inputData)
{
	const regex sourceRegex("<input(?: *([A-z]+?)=\"(.*?)\")?(?: *([A-z]+?)=\"(.*?)\")?(?: *([A-z]+?)=\"(.*?)\")?(?: *([A-z]+?)=\"(.*?)\")?.*?\/>");
	smatch sm;

	while (regex_search(inputData, sm, sourceRegex))// While regex matches are found in the file
	{
		if (sm.size() != 9)// Ensure there are 9 matches
		{
			continue;
		}

		if (!sm[0].matched)// Ensure at least match 0 found something
		{
			continue;
		}

		Input input = Input();
		ReadInput(input, sm);

		inputs.push_back(input);

		inputData = sm.suffix();// Change the source data to start where the previous match finished
	}
}

// Reads in a single input tag into an Input object
void DaeModelLoader::ReadInput(Input& input, std::smatch& match)
{
	for (size_t i = 1; i < match.size(); i += 2)// Loop through the matches in pairs, discarding the first one
	{
		if (!match[i].matched || !match[i + 1].matched)// Ensure both the current pair of matches found something
		{
			continue;
		}

		if (match[i] == "semantic")// Set the correct variable based off of the first match in the pair
		{
			input.SetSemantic(match[i + 1]);// Set the correct variable to the content of the second match in the pair
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

// Reads in a list of floats from the given data
void DaeModelLoader::ReadSpaceSepFloats(std::vector<GLfloat>& floats, std::string& line)
{
	char* word;
	char* remaining;
	word = strtok_s((char*)line.c_str(), " ", &remaining);// Find content up to a space
	while (word != NULL)// While data continues to be found
	{
		floats.push_back(stof(word));// Add the data as a float
		word = strtok_s(remaining, " ", &remaining);
	}
}

// Transfers data from Source objects into their matching Input objects by ID
void DaeModelLoader::PairInputsAndSources(std::vector<Input>& inputs, std::map<std::string, Source>& sources)
{
	for (size_t i = 0; i < inputs.size(); i++)// For every input
	{
		string key = inputs[i].GetSource();// Find the key to it's data

		if (key.length() > 0 && key[0] == '#')// Remove any hash prefixes
		{
			key = key.substr(1, key.size());
		}

		if (sources.count(key) != 0)// Add the data from the matching Source object
		{
			inputs[i].SetData(sources[key].GetData());
			inputs[i].SetDataStride(sources[key].GetStride());
		}
	}
}

// Reorders inputs by their offset, lowest to highest
void DaeModelLoader::OrderInputsByOffset(std::vector<Input>& inputs)
{
	vector<Input> sortedInputs = vector<Input>();

	for (size_t i = 0; i < inputs.size(); i++)// For every input
	{
		if (inputs[i].GetOffset() == sortedInputs.size())// If it matches the next one to be added to the results
		{
			sortedInputs.push_back(inputs[i]);// Add it to the results
			i = -1;// Reset the index to ensure any previous inputs are re-checked

			if (sortedInputs.size() == inputs.size())// If they are all sorted then the loop can end early
			{
				break;
			}
		}
	}

	inputs = sortedInputs;// Set the inputted inputs to the result
}

// Generates Vertex objects based on input data and indices
void DaeModelLoader::CreateVertices(std::vector<Vertex>& vertices, std::vector<Input>& inputs, std::vector<GLfloat>& indices)
{
	for (size_t i = 0; i < indices.size(); i += inputs.size())// For every index, chunked by how many types of data there is
	{
		Vertex newVertex = Vertex();

		for (size_t ii = 0; ii < inputs.size(); ii++)// For every specific type of data
		{
			if (inputs[ii].GetSemantic() == "VERTEX")// Add data based on the current type
			{// Which chunk of data plus the specific type within that--V     V--The stride of the type of data
				newVertex.position.x = inputs[ii].GetData()[indices[i + ii] * 3];//V--The offset within the stride
				newVertex.position.y = inputs[ii].GetData()[indices[i + ii] * 3 + 1];
				newVertex.position.z = inputs[ii].GetData()[indices[i + ii] * 3 + 2];
			}
			else if (inputs[ii].GetSemantic() == "NORMAL")
			{
				newVertex.normal.x = inputs[ii].GetData()[indices[i + ii] * 3];
				newVertex.normal.y = inputs[ii].GetData()[indices[i + ii] * 3 + 1];
				newVertex.normal.z = inputs[ii].GetData()[indices[i + ii] * 3 + 2];
			}
			else if (inputs[ii].GetSemantic() == "TEXCOORD")
			{
				newVertex.texture.x = inputs[ii].GetData()[indices[i + ii] * 2];
				newVertex.texture.y = inputs[ii].GetData()[indices[i + ii] * 2 + 1];
			}
			else if (inputs[ii].GetSemantic() == "COLOR")
			{
				newVertex.colour.r = inputs[ii].GetData()[indices[i + ii] * 4];
				newVertex.colour.g = inputs[ii].GetData()[indices[i + ii] * 4 + 1];
				newVertex.colour.b = inputs[ii].GetData()[indices[i + ii] * 4 + 2];
				newVertex.colour.a = inputs[ii].GetData()[indices[i + ii] * 4 + 3];
			}
		}

		vertices.push_back(newVertex);
	}
}

// Builds a model. This adds vertices, indices, a material, and the shader program
void DaeModelLoader::BuildModel(Model& model, Material material, std::vector<Vertex>& vertices, GLuint& program)
{
	Mesh mesh = Mesh(program);// Create a new mesh and add the vertices
	mesh.SetVertices(vertices);
	
	vector<GLuint> indices = vector<GLuint>();

	for (size_t i = 0; i < vertices.size(); i++)// Generate and add the indices. They're just a list 0-N in order
	{
		indices.push_back(i);
	}

	mesh.SetIndicies(indices);
	mesh.SetMaterial(material);// Set the material (or nothing if one was not found)

	Object object = Object(program);
	object.AddMesh(mesh);

	model.AddMaterial(material);
	model.AddObject(object);// Add the mesh to the model, wrapped in an object
}

// Loads a texture in from file
void DaeModelLoader::GetTexture(Texture& texture, string textureName, string texturePath)
{
	GLint width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* c_data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);// Load in the image data

	if (!c_data)
	{
		//TODO Error handling
	}

	texture.SetPath(textureName);
	texture.SetWidth(width);
	texture.SetHeight(height);
	texture.SetNrChannels(nrChannels);
	texture.SetData(c_data);
}